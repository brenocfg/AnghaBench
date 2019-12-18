#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct skcipher_request {int dummy; } ;
struct sk_buff {int dummy; } ;
struct scatterlist {int dummy; } ;
struct TYPE_6__ {int seq; int cksum; } ;
struct rxrpc_skb_priv {TYPE_2__ hdr; } ;
struct rxrpc_crypt {int /*<<< orphan*/  x; } ;
struct rxrpc_call {int cid; int call_id; TYPE_4__* conn; void** crypto_buf; int /*<<< orphan*/  debug_id; } ;
typedef  int /*<<< orphan*/  iv ;
struct TYPE_7__ {int security_level; int /*<<< orphan*/  key; } ;
struct TYPE_5__ {int /*<<< orphan*/  x; } ;
struct TYPE_8__ {TYPE_3__ params; int /*<<< orphan*/  cipher; TYPE_1__ csum_iv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPERM ; 
 int RXRPC_CHANNELMASK ; 
 int RXRPC_CIDSHIFT ; 
#define  RXRPC_SECURITY_AUTH 130 
#define  RXRPC_SECURITY_ENCRYPT 129 
#define  RXRPC_SECURITY_PLAIN 128 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  _leave (char*,int,int) ; 
 int /*<<< orphan*/  crypto_skcipher_encrypt (struct skcipher_request*) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  key_serial (int /*<<< orphan*/ ) ; 
 int key_validate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct rxrpc_crypt*,int /*<<< orphan*/ ,int) ; 
 int ntohl (void*) ; 
 struct skcipher_request* rxkad_get_call_crypto (struct rxrpc_call*) ; 
 int rxkad_secure_packet_auth (struct rxrpc_call*,struct sk_buff*,size_t,void*,struct skcipher_request*) ; 
 int rxkad_secure_packet_encrypt (struct rxrpc_call*,struct sk_buff*,size_t,void*,struct skcipher_request*) ; 
 struct rxrpc_skb_priv* rxrpc_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,void**,int) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (struct skcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (struct skcipher_request*,struct scatterlist*,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_sync_tfm (struct skcipher_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_zero (struct skcipher_request*) ; 

__attribute__((used)) static int rxkad_secure_packet(struct rxrpc_call *call,
			       struct sk_buff *skb,
			       size_t data_size,
			       void *sechdr)
{
	struct rxrpc_skb_priv *sp;
	struct skcipher_request	*req;
	struct rxrpc_crypt iv;
	struct scatterlist sg;
	u32 x, y;
	int ret;

	sp = rxrpc_skb(skb);

	_enter("{%d{%x}},{#%u},%zu,",
	       call->debug_id, key_serial(call->conn->params.key),
	       sp->hdr.seq, data_size);

	if (!call->conn->cipher)
		return 0;

	ret = key_validate(call->conn->params.key);
	if (ret < 0)
		return ret;

	req = rxkad_get_call_crypto(call);
	if (!req)
		return -ENOMEM;

	/* continue encrypting from where we left off */
	memcpy(&iv, call->conn->csum_iv.x, sizeof(iv));

	/* calculate the security checksum */
	x = (call->cid & RXRPC_CHANNELMASK) << (32 - RXRPC_CIDSHIFT);
	x |= sp->hdr.seq & 0x3fffffff;
	call->crypto_buf[0] = htonl(call->call_id);
	call->crypto_buf[1] = htonl(x);

	sg_init_one(&sg, call->crypto_buf, 8);
	skcipher_request_set_sync_tfm(req, call->conn->cipher);
	skcipher_request_set_callback(req, 0, NULL, NULL);
	skcipher_request_set_crypt(req, &sg, &sg, 8, iv.x);
	crypto_skcipher_encrypt(req);
	skcipher_request_zero(req);

	y = ntohl(call->crypto_buf[1]);
	y = (y >> 16) & 0xffff;
	if (y == 0)
		y = 1; /* zero checksums are not permitted */
	sp->hdr.cksum = y;

	switch (call->conn->params.security_level) {
	case RXRPC_SECURITY_PLAIN:
		ret = 0;
		break;
	case RXRPC_SECURITY_AUTH:
		ret = rxkad_secure_packet_auth(call, skb, data_size, sechdr,
					       req);
		break;
	case RXRPC_SECURITY_ENCRYPT:
		ret = rxkad_secure_packet_encrypt(call, skb, data_size,
						  sechdr, req);
		break;
	default:
		ret = -EPERM;
		break;
	}

	_leave(" = %d [set %hx]", ret, y);
	return ret;
}