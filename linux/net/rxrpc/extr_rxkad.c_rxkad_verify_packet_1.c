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
typedef  int u32 ;
typedef  int u16 ;
struct skcipher_request {int dummy; } ;
struct sk_buff {int dummy; } ;
struct scatterlist {int dummy; } ;
struct rxrpc_crypt {int /*<<< orphan*/  x; } ;
struct rxrpc_call {int call_id; TYPE_1__* conn; } ;
struct rxkad_level1_hdr {int /*<<< orphan*/  data_size; } ;
typedef  int /*<<< orphan*/  sechdr ;
typedef  int rxrpc_seq_t ;
typedef  int /*<<< orphan*/  iv ;
struct TYPE_2__ {int /*<<< orphan*/  cipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct scatterlist*) ; 
 int EPROTO ; 
 int /*<<< orphan*/  RXKADDATALEN ; 
 int /*<<< orphan*/  RXKADSEALEDINCON ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int /*<<< orphan*/  crypto_skcipher_decrypt (struct skcipher_request*) ; 
 int /*<<< orphan*/  memset (struct rxrpc_crypt*,int /*<<< orphan*/ ,int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int rxrpc_abort_eproto (struct rxrpc_call*,struct sk_buff*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_send_abort_packet (struct rxrpc_call*) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_copy_bits (struct sk_buff*,unsigned int,struct rxkad_level1_hdr*,int) ; 
 int skb_to_sgvec (struct sk_buff*,struct scatterlist*,unsigned int,int) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (struct skcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (struct skcipher_request*,struct scatterlist*,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_sync_tfm (struct skcipher_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_zero (struct skcipher_request*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int rxkad_verify_packet_1(struct rxrpc_call *call, struct sk_buff *skb,
				 unsigned int offset, unsigned int len,
				 rxrpc_seq_t seq,
				 struct skcipher_request *req)
{
	struct rxkad_level1_hdr sechdr;
	struct rxrpc_crypt iv;
	struct scatterlist sg[16];
	bool aborted;
	u32 data_size, buf;
	u16 check;
	int ret;

	_enter("");

	if (len < 8) {
		aborted = rxrpc_abort_eproto(call, skb, "rxkad_1_hdr", "V1H",
					   RXKADSEALEDINCON);
		goto protocol_error;
	}

	/* Decrypt the skbuff in-place.  TODO: We really want to decrypt
	 * directly into the target buffer.
	 */
	sg_init_table(sg, ARRAY_SIZE(sg));
	ret = skb_to_sgvec(skb, sg, offset, 8);
	if (unlikely(ret < 0))
		return ret;

	/* start the decryption afresh */
	memset(&iv, 0, sizeof(iv));

	skcipher_request_set_sync_tfm(req, call->conn->cipher);
	skcipher_request_set_callback(req, 0, NULL, NULL);
	skcipher_request_set_crypt(req, sg, sg, 8, iv.x);
	crypto_skcipher_decrypt(req);
	skcipher_request_zero(req);

	/* Extract the decrypted packet length */
	if (skb_copy_bits(skb, offset, &sechdr, sizeof(sechdr)) < 0) {
		aborted = rxrpc_abort_eproto(call, skb, "rxkad_1_len", "XV1",
					     RXKADDATALEN);
		goto protocol_error;
	}
	offset += sizeof(sechdr);
	len -= sizeof(sechdr);

	buf = ntohl(sechdr.data_size);
	data_size = buf & 0xffff;

	check = buf >> 16;
	check ^= seq ^ call->call_id;
	check &= 0xffff;
	if (check != 0) {
		aborted = rxrpc_abort_eproto(call, skb, "rxkad_1_check", "V1C",
					     RXKADSEALEDINCON);
		goto protocol_error;
	}

	if (data_size > len) {
		aborted = rxrpc_abort_eproto(call, skb, "rxkad_1_datalen", "V1L",
					     RXKADDATALEN);
		goto protocol_error;
	}

	_leave(" = 0 [dlen=%x]", data_size);
	return 0;

protocol_error:
	if (aborted)
		rxrpc_send_abort_packet(call);
	return -EPROTO;
}