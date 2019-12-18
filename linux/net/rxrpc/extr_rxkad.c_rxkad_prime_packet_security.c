#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct skcipher_request {int dummy; } ;
struct scatterlist {int dummy; } ;
struct rxrpc_key_token {TYPE_4__* kad; } ;
struct rxrpc_crypt {int /*<<< orphan*/  x; } ;
struct TYPE_11__ {int /*<<< orphan*/  cid; int /*<<< orphan*/  epoch; } ;
struct TYPE_9__ {TYPE_2__* key; } ;
struct rxrpc_connection {struct rxrpc_crypt csum_iv; TYPE_6__* cipher; int /*<<< orphan*/  security_ix; TYPE_5__ proto; TYPE_3__ params; } ;
typedef  int /*<<< orphan*/  iv ;
typedef  scalar_t__ __be32 ;
struct TYPE_12__ {int /*<<< orphan*/  base; } ;
struct TYPE_10__ {scalar_t__* session_key; } ;
struct TYPE_7__ {struct rxrpc_key_token** data; } ;
struct TYPE_8__ {TYPE_1__ payload; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  crypto_skcipher_encrypt (struct skcipher_request*) ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct rxrpc_crypt*,scalar_t__*,int) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,scalar_t__*,size_t) ; 
 struct skcipher_request* skcipher_request_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_free (struct skcipher_request*) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (struct skcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (struct skcipher_request*,struct scatterlist*,struct scatterlist*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_sync_tfm (struct skcipher_request*,TYPE_6__*) ; 

__attribute__((used)) static int rxkad_prime_packet_security(struct rxrpc_connection *conn)
{
	struct skcipher_request *req;
	struct rxrpc_key_token *token;
	struct scatterlist sg;
	struct rxrpc_crypt iv;
	__be32 *tmpbuf;
	size_t tmpsize = 4 * sizeof(__be32);

	_enter("");

	if (!conn->params.key)
		return 0;

	tmpbuf = kmalloc(tmpsize, GFP_KERNEL);
	if (!tmpbuf)
		return -ENOMEM;

	req = skcipher_request_alloc(&conn->cipher->base, GFP_NOFS);
	if (!req) {
		kfree(tmpbuf);
		return -ENOMEM;
	}

	token = conn->params.key->payload.data[0];
	memcpy(&iv, token->kad->session_key, sizeof(iv));

	tmpbuf[0] = htonl(conn->proto.epoch);
	tmpbuf[1] = htonl(conn->proto.cid);
	tmpbuf[2] = 0;
	tmpbuf[3] = htonl(conn->security_ix);

	sg_init_one(&sg, tmpbuf, tmpsize);
	skcipher_request_set_sync_tfm(req, conn->cipher);
	skcipher_request_set_callback(req, 0, NULL, NULL);
	skcipher_request_set_crypt(req, &sg, &sg, tmpsize, iv.x);
	crypto_skcipher_encrypt(req);
	skcipher_request_free(req);

	memcpy(&conn->csum_iv, tmpbuf + 2, sizeof(conn->csum_iv));
	kfree(tmpbuf);
	_leave(" = 0");
	return 0;
}