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
struct rxrpc_crypt {int /*<<< orphan*/  x; int /*<<< orphan*/ * n; } ;
struct rxrpc_connection {int dummy; } ;
struct rxkad_response {int /*<<< orphan*/  encrypted; } ;
typedef  int /*<<< orphan*/  iv ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  SKCIPHER_REQUEST_ON_STACK (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  crypto_skcipher_decrypt (int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_skcipher_setkey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (struct rxrpc_crypt*,struct rxrpc_crypt const*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  req ; 
 int /*<<< orphan*/ * rxkad_ci ; 
 int /*<<< orphan*/  rxkad_ci_mutex ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (int /*<<< orphan*/ ,struct scatterlist*,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_tfm (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_zero (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rxkad_decrypt_response(struct rxrpc_connection *conn,
				   struct rxkad_response *resp,
				   const struct rxrpc_crypt *session_key)
{
	SKCIPHER_REQUEST_ON_STACK(req, rxkad_ci);
	struct scatterlist sg[1];
	struct rxrpc_crypt iv;

	_enter(",,%08x%08x",
	       ntohl(session_key->n[0]), ntohl(session_key->n[1]));

	ASSERT(rxkad_ci != NULL);

	mutex_lock(&rxkad_ci_mutex);
	if (crypto_skcipher_setkey(rxkad_ci, session_key->x,
				   sizeof(*session_key)) < 0)
		BUG();

	memcpy(&iv, session_key, sizeof(iv));

	sg_init_table(sg, 1);
	sg_set_buf(sg, &resp->encrypted, sizeof(resp->encrypted));
	skcipher_request_set_tfm(req, rxkad_ci);
	skcipher_request_set_callback(req, 0, NULL, NULL);
	skcipher_request_set_crypt(req, sg, sg, sizeof(resp->encrypted), iv.x);
	crypto_skcipher_decrypt(req);
	skcipher_request_zero(req);

	mutex_unlock(&rxkad_ci_mutex);

	_leave("");
}