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
struct request_key_auth {struct cred const* cred; } ;
struct TYPE_4__ {int /*<<< orphan*/ * type; } ;
struct keyring_search_context {struct cred const* cred; TYPE_1__ index_key; } ;
typedef  struct cred {TYPE_3__* request_key_auth; } const cred ;
typedef  scalar_t__ key_ref_t ;
struct TYPE_5__ {struct request_key_auth** data; } ;
struct TYPE_6__ {TYPE_2__ payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  ENOKEY ; 
 scalar_t__ ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (scalar_t__) ; 
 struct cred const* current_cred () ; 
 int /*<<< orphan*/  key_type_request_key_auth ; 
 scalar_t__ key_validate (TYPE_3__*) ; 
 scalar_t__ search_cred_keyrings_rcu (struct keyring_search_context*) ; 

key_ref_t search_process_keyrings_rcu(struct keyring_search_context *ctx)
{
	struct request_key_auth *rka;
	key_ref_t key_ref, ret = ERR_PTR(-EACCES), err;

	key_ref = search_cred_keyrings_rcu(ctx);
	if (!IS_ERR(key_ref))
		goto found;
	err = key_ref;

	/* if this process has an instantiation authorisation key, then we also
	 * search the keyrings of the process mentioned there
	 * - we don't permit access to request_key auth keys via this method
	 */
	if (ctx->cred->request_key_auth &&
	    ctx->cred == current_cred() &&
	    ctx->index_key.type != &key_type_request_key_auth
	    ) {
		const struct cred *cred = ctx->cred;

		if (key_validate(cred->request_key_auth) == 0) {
			rka = ctx->cred->request_key_auth->payload.data[0];

			//// was search_process_keyrings() [ie. recursive]
			ctx->cred = rka->cred;
			key_ref = search_cred_keyrings_rcu(ctx);
			ctx->cred = cred;

			if (!IS_ERR(key_ref))
				goto found;
			ret = key_ref;
		}
	}

	/* no key - decide on the error we're going to go for */
	if (err == ERR_PTR(-ENOKEY) || ret == ERR_PTR(-ENOKEY))
		key_ref = ERR_PTR(-ENOKEY);
	else if (err == ERR_PTR(-EACCES))
		key_ref = ret;
	else
		key_ref = err;

found:
	return key_ref;
}