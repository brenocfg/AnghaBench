#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union pn48 {int val; } ;
typedef  int u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct xmit_priv {scalar_t__ frag_len; } ;
struct TYPE_4__ {int* skey; } ;
struct pkt_attrib {scalar_t__ encrypt; scalar_t__ nr_frags; int hdrlen; int iv_len; scalar_t__ last_txcmdsz; scalar_t__ icv_len; int /*<<< orphan*/  ra; int /*<<< orphan*/ * ta; TYPE_2__ dot118021x_UncstKey; } ;
struct xmit_frame {int* buf_addr; struct pkt_attrib attrib; } ;
struct security_priv {size_t dot118021XGrpKeyid; TYPE_1__* dot118021XGrpKey; } ;
struct arc4context {int dummy; } ;
struct adapter {struct xmit_priv xmitpriv; struct security_priv securitypriv; } ;
typedef  scalar_t__ sint ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_3__ {int* skey; } ;
typedef  int /*<<< orphan*/  SIZE_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  GET_TKIP_PN (int*,union pn48) ; 
 scalar_t__ IS_MCAST (int /*<<< orphan*/ ) ; 
 scalar_t__ RND4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TKIP_SW_ENC_CNT_INC (struct security_priv*,int /*<<< orphan*/ ) ; 
 int TXDESC_OFFSET ; 
 int _FAIL ; 
 int _SUCCESS ; 
 scalar_t__ _TKIP_ ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_security_c_ ; 
 int /*<<< orphan*/  arcfour_encrypt (struct arc4context*,int*,int*,int) ; 
 int /*<<< orphan*/  arcfour_init (struct arc4context*,int*,int) ; 
 int /*<<< orphan*/  getcrc32 (int*,scalar_t__) ; 
 int /*<<< orphan*/  phase1 (scalar_t__*,int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  phase2 (int*,int*,scalar_t__*,scalar_t__) ; 

u32 rtw_tkip_encrypt(struct adapter *padapter, u8 *pxmitframe)
{																	/*  exclude ICV */
	u16 pnl;
	u32 pnh;
	u8 rc4key[16];
	u8   ttkey[16];
	u8 crc[4];
	u8   hw_hdr_offset = 0;
	struct arc4context mycontext;
	sint			curfragnum, length;
	u32 prwskeylen;

	u8 *pframe, *payload, *iv, *prwskey;
	union pn48 dot11txpn;
	/* struct	sta_info 	*stainfo; */
	struct	pkt_attrib	 *pattrib = &((struct xmit_frame *)pxmitframe)->attrib;
	struct	security_priv *psecuritypriv = &padapter->securitypriv;
	struct	xmit_priv 	*pxmitpriv = &padapter->xmitpriv;
	u32 res = _SUCCESS;

	if (((struct xmit_frame *)pxmitframe)->buf_addr == NULL)
		return _FAIL;

	hw_hdr_offset = TXDESC_OFFSET;
	pframe = ((struct xmit_frame *)pxmitframe)->buf_addr + hw_hdr_offset;

	/* 4 start to encrypt each fragment */
	if (pattrib->encrypt == _TKIP_) {

/*
		if (pattrib->psta)
		{
			stainfo = pattrib->psta;
		}
		else
		{
			DBG_871X("%s, call rtw_get_stainfo()\n", __func__);
			stainfo =rtw_get_stainfo(&padapter->stapriv ,&pattrib->ra[0]);
		}
*/
		/* if (stainfo!= NULL) */
		{
/*
			if (!(stainfo->state &_FW_LINKED))
			{
				DBG_871X("%s, psta->state(0x%x) != _FW_LINKED\n", __func__, stainfo->state);
				return _FAIL;
			}
*/
			RT_TRACE(_module_rtl871x_security_c_, _drv_err_, ("rtw_tkip_encrypt: stainfo!= NULL!!!\n"));

			if (IS_MCAST(pattrib->ra))
				prwskey = psecuritypriv->dot118021XGrpKey[psecuritypriv->dot118021XGrpKeyid].skey;
			else
				/* prwskey =&stainfo->dot118021x_UncstKey.skey[0]; */
				prwskey = pattrib->dot118021x_UncstKey.skey;

			prwskeylen = 16;

			for (curfragnum = 0; curfragnum < pattrib->nr_frags; curfragnum++) {
				iv = pframe+pattrib->hdrlen;
				payload = pframe+pattrib->iv_len+pattrib->hdrlen;

				GET_TKIP_PN(iv, dot11txpn);

				pnl = (u16)(dot11txpn.val);
				pnh = (u32)(dot11txpn.val>>16);

				phase1((u16 *)&ttkey[0], prwskey, &pattrib->ta[0], pnh);

				phase2(&rc4key[0], prwskey, (u16 *)&ttkey[0], pnl);

				if ((curfragnum+1) == pattrib->nr_frags) {	/* 4 the last fragment */
					length = pattrib->last_txcmdsz-pattrib->hdrlen-pattrib->iv_len-pattrib->icv_len;
					RT_TRACE(_module_rtl871x_security_c_, _drv_info_, ("pattrib->iv_len =%x, pattrib->icv_len =%x\n", pattrib->iv_len, pattrib->icv_len));
					*((__le32 *)crc) = getcrc32(payload, length);/* modified by Amy*/

					arcfour_init(&mycontext, rc4key, 16);
					arcfour_encrypt(&mycontext, payload, payload, length);
					arcfour_encrypt(&mycontext, payload+length, crc, 4);

				} else {
					length = pxmitpriv->frag_len-pattrib->hdrlen-pattrib->iv_len-pattrib->icv_len;
					*((__le32 *)crc) = getcrc32(payload, length);/* modified by Amy*/
					arcfour_init(&mycontext, rc4key, 16);
					arcfour_encrypt(&mycontext, payload, payload, length);
					arcfour_encrypt(&mycontext, payload+length, crc, 4);

					pframe += pxmitpriv->frag_len;
					pframe = (u8 *)RND4((SIZE_PTR)(pframe));
				}
			}

			TKIP_SW_ENC_CNT_INC(psecuritypriv, pattrib->ra);
		}
/*
		else {
			RT_TRACE(_module_rtl871x_security_c_, _drv_err_, ("rtw_tkip_encrypt: stainfo == NULL!!!\n"));
			DBG_871X("%s, psta ==NUL\n", __func__);
			res = _FAIL;
		}
*/

	}
	return res;
}