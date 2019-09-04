#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct xmit_priv {scalar_t__ frag_len; } ;
struct pkt_attrib {scalar_t__ encrypt; scalar_t__ nr_frags; scalar_t__ last_txcmdsz; scalar_t__ hdrlen; scalar_t__ iv_len; scalar_t__ icv_len; int /*<<< orphan*/ * ra; struct sta_info* psta; } ;
struct xmit_frame {int /*<<< orphan*/ * buf_addr; struct pkt_attrib attrib; } ;
struct TYPE_2__ {int /*<<< orphan*/ * skey; } ;
struct sta_info {TYPE_1__ x_UncstKey; } ;
struct _adapter {int /*<<< orphan*/  stapriv; struct xmit_priv xmitpriv; } ;
typedef  scalar_t__ sint ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 scalar_t__ RND4 (int /*<<< orphan*/ ) ; 
 int TXDESC_OFFSET ; 
 scalar_t__ _AES_ ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  aes_cipher (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 struct sta_info* r8712_get_stainfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

u32 r8712_aes_encrypt(struct _adapter *padapter, u8 *pxmitframe)
{	/* exclude ICV */
	/* Intermediate Buffers */
	sint	curfragnum, length;
	u8	*pframe, *prwskey;
	struct	sta_info *stainfo;
	struct	pkt_attrib  *pattrib = &((struct xmit_frame *)
				       pxmitframe)->attrib;
	struct	xmit_priv *pxmitpriv = &padapter->xmitpriv;
	u32 res = _SUCCESS;

	if (((struct xmit_frame *)pxmitframe)->buf_addr == NULL)
		return _FAIL;
	pframe = ((struct xmit_frame *)pxmitframe)->buf_addr + TXDESC_OFFSET;
	/* 4 start to encrypt each fragment */
	if (pattrib->encrypt == _AES_) {
		if (pattrib->psta)
			stainfo = pattrib->psta;
		else
			stainfo = r8712_get_stainfo(&padapter->stapriv,
				  &pattrib->ra[0]);
		if (stainfo != NULL) {
			prwskey = &stainfo->x_UncstKey.skey[0];
			for (curfragnum = 0; curfragnum < pattrib->nr_frags;
			     curfragnum++) {
				if ((curfragnum + 1) == pattrib->nr_frags) {
					length = pattrib->last_txcmdsz -
						 pattrib->hdrlen -
						 pattrib->iv_len -
						 pattrib->icv_len;
					aes_cipher(prwskey, pattrib->hdrlen,
						   pframe, length);
				} else {
					length = pxmitpriv->frag_len -
						 pattrib->hdrlen -
						 pattrib->iv_len -
						 pattrib->icv_len;
					aes_cipher(prwskey, pattrib->hdrlen,
						   pframe, length);
					pframe += pxmitpriv->frag_len;
					pframe = (u8 *)RND4((addr_t)(pframe));
				}
			}
		} else {
			res = _FAIL;
		}
	}
	return res;
}