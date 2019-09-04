#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char u8 ;
typedef  int u32 ;
struct xmit_priv {scalar_t__ frag_len; } ;
struct pkt_attrib {scalar_t__ encrypt; scalar_t__ nr_frags; int hdrlen; int iv_len; scalar_t__ last_txcmdsz; scalar_t__ icv_len; } ;
struct xmit_frame {unsigned char* buf_addr; struct pkt_attrib attrib; } ;
struct security_priv {int* dot11DefKeylen; size_t dot11PrivacyKeyIndex; TYPE_1__* dot11DefKey; } ;
struct arc4context {int dummy; } ;
typedef  scalar_t__ sint ;
struct TYPE_5__ {struct xmit_priv xmitpriv; struct security_priv securitypriv; } ;
typedef  TYPE_2__ _adapter ;
struct TYPE_4__ {unsigned char* skey; } ;
typedef  int /*<<< orphan*/  SIZE_PTR ;

/* Variables and functions */
 scalar_t__ RND4 (int /*<<< orphan*/ ) ; 
 int TXDESC_OFFSET ; 
 scalar_t__ _WEP104_ ; 
 scalar_t__ _WEP40_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _rtw_memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  arcfour_encrypt (struct arc4context*,unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  arcfour_init (struct arc4context*,unsigned char*,int) ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getcrc32 (unsigned char*,scalar_t__) ; 

void rtw_wep_encrypt(_adapter *padapter, u8 *pxmitframe)
{																	// exclude ICV
	
	unsigned char	crc[4];
	struct arc4context	 mycontext;

	sint	curfragnum,length;
	u32	keylength;

	u8	*pframe, *payload,*iv;    //,*wepkey
	u8	wepkey[16];
	struct	pkt_attrib	 *pattrib = &((struct xmit_frame*)pxmitframe)->attrib;
	struct 	security_priv	*psecuritypriv=&padapter->securitypriv;
	struct	xmit_priv		*pxmitpriv=&padapter->xmitpriv;
	
_func_enter_;	

	
	if(((struct xmit_frame*)pxmitframe)->buf_addr==NULL)
		return;

#ifdef CONFIG_USB_TX_AGGREGATION
	pframe = ((struct xmit_frame*)pxmitframe)->buf_addr + TXDESC_SIZE +
		 (((struct xmit_frame*)pxmitframe)->pkt_offset * PACKET_OFFSET_SZ);
#else
	pframe = ((struct xmit_frame*)pxmitframe)->buf_addr + TXDESC_OFFSET;
#endif
	
	//start to encrypt each fragment
	if((pattrib->encrypt==_WEP40_)||(pattrib->encrypt==_WEP104_))
	{
		keylength=psecuritypriv->dot11DefKeylen[psecuritypriv->dot11PrivacyKeyIndex];

		for(curfragnum=0;curfragnum<pattrib->nr_frags;curfragnum++)
		{
			iv=pframe+pattrib->hdrlen;
			_rtw_memcpy(&wepkey[0], iv, 3);
			_rtw_memcpy(&wepkey[3], &psecuritypriv->dot11DefKey[psecuritypriv->dot11PrivacyKeyIndex].skey[0],keylength);
			payload=pframe+pattrib->iv_len+pattrib->hdrlen;

			if((curfragnum+1)==pattrib->nr_frags)
			{	//the last fragment
			
				length=pattrib->last_txcmdsz-pattrib->hdrlen-pattrib->iv_len- pattrib->icv_len;
			
				*((u32 *)crc)=cpu_to_le32(getcrc32(payload,length));

				arcfour_init(&mycontext, wepkey,3+keylength);
				arcfour_encrypt(&mycontext, payload, payload, length);
				arcfour_encrypt(&mycontext, payload+length, crc, 4);

			}
			else
			{
			length=pxmitpriv->frag_len-pattrib->hdrlen-pattrib->iv_len-pattrib->icv_len ;
				*((u32 *)crc)=cpu_to_le32(getcrc32(payload,length));
				arcfour_init(&mycontext, wepkey,3+keylength);
				arcfour_encrypt(&mycontext, payload, payload, length);
				arcfour_encrypt(&mycontext, payload+length, crc, 4);
	
			pframe+=pxmitpriv->frag_len;
			pframe=(u8 *)RND4((SIZE_PTR)(pframe));

			}
			
		}		
						
	}
	
_func_exit_;						

}