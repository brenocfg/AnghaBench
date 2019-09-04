#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rx_pkt_attrib {scalar_t__ encrypt; int hdrlen; int iv_len; } ;
struct TYPE_5__ {int len; scalar_t__ rx_data; struct rx_pkt_attrib attrib; } ;
struct TYPE_6__ {TYPE_2__ hdr; } ;
union recv_frame {TYPE_3__ u; } ;
typedef  int u8 ;
typedef  int u32 ;
struct security_priv {int* DefKeylen; size_t PrivacyKeyIndex; TYPE_1__* DefKey; } ;
struct arc4context {int dummy; } ;
struct _adapter {struct security_priv securitypriv; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_4__ {int* skey; } ;

/* Variables and functions */
 scalar_t__ _WEP104_ ; 
 scalar_t__ _WEP40_ ; 
 int /*<<< orphan*/  arcfour_encrypt (struct arc4context*,int*,int*,int) ; 
 int /*<<< orphan*/  arcfour_init (struct arc4context*,int*,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getcrc32 (int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

void r8712_wep_decrypt(struct _adapter  *padapter, u8 *precvframe)
{
	/* exclude ICV */
	u8 crc[4];
	struct arc4context  mycontext;
	u32 length, keylength;
	u8 *pframe, *payload, *iv, wepkey[16];
	u8  keyindex;
	struct rx_pkt_attrib  *prxattrib = &(((union recv_frame *)
					  precvframe)->u.hdr.attrib);
	struct security_priv *psecuritypriv = &padapter->securitypriv;

	pframe = (unsigned char *)((union recv_frame *)precvframe)->
		  u.hdr.rx_data;
	/* start to decrypt recvframe */
	if ((prxattrib->encrypt == _WEP40_) || (prxattrib->encrypt ==
	     _WEP104_)) {
		iv = pframe + prxattrib->hdrlen;
		keyindex = (iv[3] & 0x3);
		keylength = psecuritypriv->DefKeylen[keyindex];
		memcpy(&wepkey[0], iv, 3);
		memcpy(&wepkey[3], &psecuritypriv->DefKey[
			psecuritypriv->PrivacyKeyIndex].skey[0],
			keylength);
		length = ((union recv_frame *)precvframe)->
			   u.hdr.len - prxattrib->hdrlen - prxattrib->iv_len;
		payload = pframe + prxattrib->iv_len + prxattrib->hdrlen;
		/* decrypt payload include icv */
		arcfour_init(&mycontext, wepkey, 3 + keylength);
		arcfour_encrypt(&mycontext, payload, payload,  length);
		/* calculate icv and compare the icv */
		*((__le32 *)crc) = cpu_to_le32(getcrc32(payload, length - 4));
	}
}