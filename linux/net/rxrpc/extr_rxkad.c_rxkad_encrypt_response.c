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
struct skcipher_request {int dummy; } ;
struct scatterlist {int dummy; } ;
struct rxrpc_crypt {int /*<<< orphan*/  x; } ;
struct rxrpc_connection {TYPE_1__* cipher; } ;
struct rxkad_response {int /*<<< orphan*/  encrypted; } ;
struct rxkad_key {int /*<<< orphan*/  session_key; } ;
typedef  int /*<<< orphan*/  iv ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  crypto_skcipher_encrypt (struct skcipher_request*) ; 
 int /*<<< orphan*/  memcpy (struct rxrpc_crypt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,int /*<<< orphan*/ *,int) ; 
 struct skcipher_request* skcipher_request_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_free (struct skcipher_request*) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (struct skcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (struct skcipher_request*,struct scatterlist*,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_sync_tfm (struct skcipher_request*,TYPE_1__*) ; 

__attribute__((used)) static int rxkad_encrypt_response(struct rxrpc_connection *conn,
				  struct rxkad_response *resp,
				  const struct rxkad_key *s2)
{
	struct skcipher_request *req;
	struct rxrpc_crypt iv;
	struct scatterlist sg[1];

	req = skcipher_request_alloc(&conn->cipher->base, GFP_NOFS);
	if (!req)
		return -ENOMEM;

	/* continue encrypting from where we left off */
	memcpy(&iv, s2->session_key, sizeof(iv));

	sg_init_table(sg, 1);
	sg_set_buf(sg, &resp->encrypted, sizeof(resp->encrypted));
	skcipher_request_set_sync_tfm(req, conn->cipher);
	skcipher_request_set_callback(req, 0, NULL, NULL);
	skcipher_request_set_crypt(req, sg, sg, sizeof(resp->encrypted), iv.x);
	crypto_skcipher_encrypt(req);
	skcipher_request_free(req);
	return 0;
}