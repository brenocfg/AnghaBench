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
typedef  int u32 ;
typedef  int u16 ;
struct skcipher_request {int dummy; } ;
struct sk_buff {int dummy; } ;
struct scatterlist {int dummy; } ;
struct rxrpc_crypt {int /*<<< orphan*/  x; } ;
struct rxrpc_call {int cid; int call_id; TYPE_3__* conn; void** crypto_buf; int /*<<< orphan*/  debug_id; } ;
typedef  int rxrpc_seq_t ;
typedef  int /*<<< orphan*/  iv ;
struct TYPE_5__ {int security_level; int /*<<< orphan*/  key; } ;
struct TYPE_4__ {int /*<<< orphan*/  x; } ;
struct TYPE_6__ {TYPE_2__ params; int /*<<< orphan*/  cipher; TYPE_1__ csum_iv; } ;

/* Variables and functions */
 int ENOANO ; 
 int ENOMEM ; 
 int EPROTO ; 
 int /*<<< orphan*/  RXKADSEALEDINCON ; 
 int RXRPC_CHANNELMASK ; 
 int RXRPC_CIDSHIFT ; 
#define  RXRPC_SECURITY_AUTH 130 
#define  RXRPC_SECURITY_ENCRYPT 129 
#define  RXRPC_SECURITY_PLAIN 128 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  crypto_skcipher_encrypt (struct skcipher_request*) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  key_serial (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct rxrpc_crypt*,int /*<<< orphan*/ ,int) ; 
 int ntohl (void*) ; 
 struct skcipher_request* rxkad_get_call_crypto (struct rxrpc_call*) ; 
 int rxkad_verify_packet_1 (struct rxrpc_call*,struct sk_buff*,unsigned int,unsigned int,int,struct skcipher_request*) ; 
 int rxkad_verify_packet_2 (struct rxrpc_call*,struct sk_buff*,unsigned int,unsigned int,int,struct skcipher_request*) ; 
 int rxrpc_abort_eproto (struct rxrpc_call*,struct sk_buff*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_send_abort_packet (struct rxrpc_call*) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,void**,int) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (struct skcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (struct skcipher_request*,struct scatterlist*,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_sync_tfm (struct skcipher_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_zero (struct skcipher_request*) ; 

__attribute__((used)) static int rxkad_verify_packet(struct rxrpc_call *call, struct sk_buff *skb,
			       unsigned int offset, unsigned int len,
			       rxrpc_seq_t seq, u16 expected_cksum)
{
	struct skcipher_request	*req;
	struct rxrpc_crypt iv;
	struct scatterlist sg;
	bool aborted;
	u16 cksum;
	u32 x, y;

	_enter("{%d{%x}},{#%u}",
	       call->debug_id, key_serial(call->conn->params.key), seq);

	if (!call->conn->cipher)
		return 0;

	req = rxkad_get_call_crypto(call);
	if (!req)
		return -ENOMEM;

	/* continue encrypting from where we left off */
	memcpy(&iv, call->conn->csum_iv.x, sizeof(iv));

	/* validate the security checksum */
	x = (call->cid & RXRPC_CHANNELMASK) << (32 - RXRPC_CIDSHIFT);
	x |= seq & 0x3fffffff;
	call->crypto_buf[0] = htonl(call->call_id);
	call->crypto_buf[1] = htonl(x);

	sg_init_one(&sg, call->crypto_buf, 8);
	skcipher_request_set_sync_tfm(req, call->conn->cipher);
	skcipher_request_set_callback(req, 0, NULL, NULL);
	skcipher_request_set_crypt(req, &sg, &sg, 8, iv.x);
	crypto_skcipher_encrypt(req);
	skcipher_request_zero(req);

	y = ntohl(call->crypto_buf[1]);
	cksum = (y >> 16) & 0xffff;
	if (cksum == 0)
		cksum = 1; /* zero checksums are not permitted */

	if (cksum != expected_cksum) {
		aborted = rxrpc_abort_eproto(call, skb, "rxkad_csum", "VCK",
					     RXKADSEALEDINCON);
		goto protocol_error;
	}

	switch (call->conn->params.security_level) {
	case RXRPC_SECURITY_PLAIN:
		return 0;
	case RXRPC_SECURITY_AUTH:
		return rxkad_verify_packet_1(call, skb, offset, len, seq, req);
	case RXRPC_SECURITY_ENCRYPT:
		return rxkad_verify_packet_2(call, skb, offset, len, seq, req);
	default:
		return -ENOANO;
	}

protocol_error:
	if (aborted)
		rxrpc_send_abort_packet(call);
	return -EPROTO;
}