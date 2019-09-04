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
typedef  char u8 ;
struct sk_buff {char* data; int len; } ;
struct security_priv {int /*<<< orphan*/ * dot11DefKeylen; TYPE_1__* dot11DefKey; } ;
struct rx_pkt_attrib {scalar_t__ encrypt; int key_index; int hdrlen; } ;
struct recv_frame {struct sk_buff* pkt; struct rx_pkt_attrib attrib; } ;
struct lib80211_crypto_ops {scalar_t__ (* set_key ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ;int /*<<< orphan*/  (* deinit ) (void*) ;scalar_t__ (* decrypt_mpdu ) (struct sk_buff*,int,void*) ;void* (* init ) (int const) ;} ;
struct adapter {struct security_priv securitypriv; } ;
struct TYPE_2__ {int /*<<< orphan*/  skey; } ;

/* Variables and functions */
 int _FAIL ; 
 int _SUCCESS ; 
 scalar_t__ _WEP104_ ; 
 scalar_t__ _WEP40_ ; 
 struct lib80211_crypto_ops* lib80211_get_crypto_ops (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 void* stub1 (int const) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 scalar_t__ stub3 (struct sk_buff*,int,void*) ; 
 int /*<<< orphan*/  stub4 (void*) ; 

int rtw_wep_decrypt(struct adapter  *padapter, u8 *precvframe)
{
	struct	rx_pkt_attrib	 *prxattrib = &(((struct recv_frame *)precvframe)->attrib);

	if ((prxattrib->encrypt == _WEP40_) || (prxattrib->encrypt == _WEP104_)) {
		struct	security_priv	*psecuritypriv = &padapter->securitypriv;
		struct sk_buff *skb = ((struct recv_frame *)precvframe)->pkt;
		u8 *pframe = skb->data;
		void *crypto_private = NULL;
		int status = _SUCCESS;
		const int keyindex = prxattrib->key_index;
		struct lib80211_crypto_ops *crypto_ops = lib80211_get_crypto_ops("WEP");
		char iv[4], icv[4];

		if (!crypto_ops) {
			status = _FAIL;
			goto exit;
		}

		memcpy(iv, pframe + prxattrib->hdrlen, 4);
		memcpy(icv, pframe + skb->len - 4, 4);

		crypto_private = crypto_ops->init(keyindex);
		if (!crypto_private) {
			status = _FAIL;
			goto exit;
		}
		if (crypto_ops->set_key(psecuritypriv->dot11DefKey[keyindex].skey,
					psecuritypriv->dot11DefKeylen[keyindex], NULL, crypto_private) < 0) {
			status = _FAIL;
			goto exit;
		}
		if (crypto_ops->decrypt_mpdu(skb, prxattrib->hdrlen, crypto_private)) {
			status = _FAIL;
			goto exit;
		}

		memmove(pframe, pframe + 4, prxattrib->hdrlen);
		skb_push(skb, 4);
		skb_put(skb, 4);

		memcpy(pframe + prxattrib->hdrlen, iv, 4);
		memcpy(pframe + skb->len - 4, icv, 4);

exit:
		if (crypto_ops && crypto_private)
			crypto_ops->deinit(crypto_private);
		return status;
	}

	return _FAIL;
}