#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct skcipher_request {int dummy; } ;
struct rxrpc_call {struct skcipher_request* cipher_req; TYPE_2__* conn; } ;
struct crypto_skcipher {int dummy; } ;
struct TYPE_4__ {TYPE_1__* cipher; } ;
struct TYPE_3__ {struct crypto_skcipher base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 struct skcipher_request* skcipher_request_alloc (struct crypto_skcipher*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct skcipher_request *rxkad_get_call_crypto(struct rxrpc_call *call)
{
	struct crypto_skcipher *tfm = &call->conn->cipher->base;
	struct skcipher_request	*cipher_req = call->cipher_req;

	if (!cipher_req) {
		cipher_req = skcipher_request_alloc(tfm, GFP_NOFS);
		if (!cipher_req)
			return NULL;
		call->cipher_req = cipher_req;
	}

	return cipher_req;
}