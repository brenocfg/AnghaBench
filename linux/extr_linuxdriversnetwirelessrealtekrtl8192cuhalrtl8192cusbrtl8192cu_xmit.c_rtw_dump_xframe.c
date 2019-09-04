#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct xmit_priv {int frag_len; } ;
struct pkt_attrib {int ether_type; int dhcp_pkt; int nr_frags; int icv_len; int last_txcmdsz; } ;
struct xmit_frame {scalar_t__ frame_tag; int /*<<< orphan*/ * buf_addr; struct pkt_attrib attrib; struct xmit_buf* pxmitbuf; } ;
struct xmit_buf {int /*<<< orphan*/  sctx; } ;
struct security_priv {scalar_t__ sw_encrypt; } ;
typedef  scalar_t__ s32 ;
struct TYPE_6__ {struct security_priv securitypriv; struct xmit_priv xmitpriv; } ;
typedef  TYPE_1__ _adapter ;
typedef  int /*<<< orphan*/  SIZE_PTR ;

/* Variables and functions */
 scalar_t__ DATA_FRAMETAG ; 
 int PACKET_OFFSET_SZ ; 
 scalar_t__ RND4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTW_SCTX_DONE_UNKNOWN ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int TXDESC_SIZE ; 
 scalar_t__ _FAIL ; 
 int /*<<< orphan*/  _FALSE ; 
 scalar_t__ _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_xmit_c_ ; 
 int /*<<< orphan*/  rtw_count_tx_stats (TYPE_1__*,struct xmit_frame*,int) ; 
 int /*<<< orphan*/  rtw_free_xmitframe (struct xmit_priv*,struct xmit_frame*) ; 
 int /*<<< orphan*/  rtw_get_ff_hwaddr (struct xmit_frame*) ; 
 int /*<<< orphan*/  rtw_issue_addbareq_cmd (TYPE_1__*,struct xmit_frame*) ; 
 int /*<<< orphan*/  rtw_sctx_done_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ rtw_write_port (TYPE_1__*,int /*<<< orphan*/ ,int,unsigned char*) ; 
 int update_txdesc (struct xmit_frame*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 rtw_dump_xframe(_adapter *padapter, struct xmit_frame *pxmitframe)
{
	s32 ret = _SUCCESS;
	s32 inner_ret = _SUCCESS;
	int t, sz, w_sz, pull=0;
	u8 *mem_addr;
	u32 ff_hwaddr;
	struct xmit_buf *pxmitbuf = pxmitframe->pxmitbuf;
	struct pkt_attrib *pattrib = &pxmitframe->attrib;
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;
	struct security_priv *psecuritypriv = &padapter->securitypriv;

	if ((pxmitframe->frame_tag == DATA_FRAMETAG) &&
	    (pxmitframe->attrib.ether_type != 0x0806) &&
	    (pxmitframe->attrib.ether_type != 0x888e) &&
	    (pxmitframe->attrib.dhcp_pkt != 1))
	{
		rtw_issue_addbareq_cmd(padapter, pxmitframe);
	}
	
	mem_addr = pxmitframe->buf_addr;

       RT_TRACE(_module_rtl871x_xmit_c_,_drv_info_,("rtw_dump_xframe()\n"));
	
	for (t = 0; t < pattrib->nr_frags; t++)
	{
		if (inner_ret != _SUCCESS && ret == _SUCCESS)
			ret = _FAIL;

		if (t != (pattrib->nr_frags - 1))
		{
			RT_TRACE(_module_rtl871x_xmit_c_,_drv_err_,("pattrib->nr_frags=%d\n", pattrib->nr_frags));

			sz = pxmitpriv->frag_len;
			sz = sz - 4 - (psecuritypriv->sw_encrypt ? 0 : pattrib->icv_len);					
		}
		else //no frag
		{
			sz = pattrib->last_txcmdsz;
		}

		pull = update_txdesc(pxmitframe, mem_addr, sz, _FALSE);
		
		if(pull)
		{
			mem_addr += PACKET_OFFSET_SZ; //pull txdesc head
			
			//pxmitbuf ->pbuf = mem_addr;			
			pxmitframe->buf_addr = mem_addr;

			w_sz = sz + TXDESC_SIZE;
		}
		else
		{
			w_sz = sz + TXDESC_SIZE + PACKET_OFFSET_SZ;
		}	

		ff_hwaddr = rtw_get_ff_hwaddr(pxmitframe);
		
		inner_ret = rtw_write_port(padapter, ff_hwaddr, w_sz, (unsigned char*)pxmitbuf);

		rtw_count_tx_stats(padapter, pxmitframe, sz);


		RT_TRACE(_module_rtl871x_xmit_c_,_drv_info_,("rtw_write_port, w_sz=%d\n", w_sz));
		//DBG_8192C("rtw_write_port, w_sz=%d, sz=%d, txdesc_sz=%d, tid=%d\n", w_sz, sz, w_sz-sz, pattrib->priority);      

		mem_addr += w_sz;

		mem_addr = (u8 *)RND4(((SIZE_PTR)(mem_addr)));

	}
	
	rtw_free_xmitframe(pxmitpriv, pxmitframe);

	if  (ret != _SUCCESS)
		rtw_sctx_done_err(&pxmitbuf->sctx, RTW_SCTX_DONE_UNKNOWN);

	return ret;
}