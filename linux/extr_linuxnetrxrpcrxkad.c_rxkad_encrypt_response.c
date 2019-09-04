#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct scatterlist {int dummy; } ;
struct rxrpc_crypt {int /*<<< orphan*/  x; } ;
struct rxrpc_connection {int /*<<< orphan*/  cipher; } ;
struct rxkad_response {int /*<<< orphan*/  encrypted; } ;
struct rxkad_key {int /*<<< orphan*/  session_key; } ;
typedef  int /*<<< orphan*/  iv ;

/* Variables and functions */
 int /*<<< orphan*/  SKCIPHER_REQUEST_ON_STACK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_skcipher_encrypt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct rxrpc_crypt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  req ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (int /*<<< orphan*/ ,struct scatterlist*,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_tfm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_zero (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rxkad_encrypt_response(struct rxrpc_connection *conn,
				   struct rxkad_response *resp,
				   const struct rxkad_key *s2)
{
	SKCIPHER_REQUEST_ON_STACK(req, conn->cipher);
	struct rxrpc_crypt iv;
	struct scatterlist sg[1];

	/* continue encrypting from where we left off */
	memcpy(&iv, s2->session_key, sizeof(iv));

	sg_init_table(sg, 1);
	sg_set_buf(sg, &resp->encrypted, sizeof(resp->encrypted));
	skcipher_request_set_tfm(req, conn->cipher);
	skcipher_request_set_callback(req, 0, NULL, NULL);
	skcipher_request_set_crypt(req, sg, sg, sizeof(resp->encrypted), iv.x);
	crypto_skcipher_encrypt(req);
	skcipher_request_zero(req);
}