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
struct keyring_search_context {int flags; int /*<<< orphan*/  result; int /*<<< orphan*/  now; int /*<<< orphan*/  cred; int /*<<< orphan*/  possessed; int /*<<< orphan*/  iterator; } ;
struct key {int /*<<< orphan*/ * type; } ;
typedef  int /*<<< orphan*/  key_ref_t ;

/* Variables and functions */
 long EAGAIN ; 
 long ENOTDIR ; 
 int /*<<< orphan*/  ERR_PTR (long) ; 
 int KEYRING_SEARCH_NO_CHECK_PERM ; 
 int /*<<< orphan*/  KEY_NEED_SEARCH ; 
 int /*<<< orphan*/  __key_get (struct key*) ; 
 int /*<<< orphan*/  is_key_possessed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_check (struct key*) ; 
 struct key* key_ref_to_ptr (int /*<<< orphan*/ ) ; 
 long key_task_permission (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_type_keyring ; 
 int /*<<< orphan*/  keyring_search_iterator ; 
 int /*<<< orphan*/  ktime_get_real_seconds () ; 
 scalar_t__ search_nested_keyrings (struct key*,struct keyring_search_context*) ; 

key_ref_t keyring_search_rcu(key_ref_t keyring_ref,
			     struct keyring_search_context *ctx)
{
	struct key *keyring;
	long err;

	ctx->iterator = keyring_search_iterator;
	ctx->possessed = is_key_possessed(keyring_ref);
	ctx->result = ERR_PTR(-EAGAIN);

	keyring = key_ref_to_ptr(keyring_ref);
	key_check(keyring);

	if (keyring->type != &key_type_keyring)
		return ERR_PTR(-ENOTDIR);

	if (!(ctx->flags & KEYRING_SEARCH_NO_CHECK_PERM)) {
		err = key_task_permission(keyring_ref, ctx->cred, KEY_NEED_SEARCH);
		if (err < 0)
			return ERR_PTR(err);
	}

	ctx->now = ktime_get_real_seconds();
	if (search_nested_keyrings(keyring, ctx))
		__key_get(key_ref_to_ptr(ctx->result));
	return ctx->result;
}