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
struct TYPE_3__ {char* description; int /*<<< orphan*/  desc_len; int /*<<< orphan*/ * type; } ;
struct TYPE_4__ {char* raw_data; int /*<<< orphan*/  lookup_type; int /*<<< orphan*/  cmp; } ;
struct keyring_search_context {int flags; TYPE_1__ index_key; TYPE_2__ match_data; int /*<<< orphan*/  cred; } ;
struct key {int /*<<< orphan*/  flags; } ;
typedef  int key_serial_t ;
typedef  int /*<<< orphan*/  key_ref_t ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EKEYREVOKED ; 
 int /*<<< orphan*/  ENOKEY ; 
 struct key* ERR_CAST (int /*<<< orphan*/ ) ; 
 struct key* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int KEYRING_SEARCH_DO_STATE_CHECK ; 
 int /*<<< orphan*/  KEYRING_SEARCH_LOOKUP_DIRECT ; 
 int KEYRING_SEARCH_RECURSE ; 
 int /*<<< orphan*/  KEY_FLAG_REVOKED ; 
 int /*<<< orphan*/  current_cred () ; 
 int /*<<< orphan*/  key_default_cmp ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 struct key* key_ref_to_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_type_request_key_auth ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  search_process_keyrings_rcu (struct keyring_search_context*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct key *key_get_instantiation_authkey(key_serial_t target_id)
{
	char description[16];
	struct keyring_search_context ctx = {
		.index_key.type		= &key_type_request_key_auth,
		.index_key.description	= description,
		.cred			= current_cred(),
		.match_data.cmp		= key_default_cmp,
		.match_data.raw_data	= description,
		.match_data.lookup_type	= KEYRING_SEARCH_LOOKUP_DIRECT,
		.flags			= (KEYRING_SEARCH_DO_STATE_CHECK |
					   KEYRING_SEARCH_RECURSE),
	};
	struct key *authkey;
	key_ref_t authkey_ref;

	ctx.index_key.desc_len = sprintf(description, "%x", target_id);

	rcu_read_lock();
	authkey_ref = search_process_keyrings_rcu(&ctx);
	rcu_read_unlock();

	if (IS_ERR(authkey_ref)) {
		authkey = ERR_CAST(authkey_ref);
		if (authkey == ERR_PTR(-EAGAIN))
			authkey = ERR_PTR(-ENOKEY);
		goto error;
	}

	authkey = key_ref_to_ptr(authkey_ref);
	if (test_bit(KEY_FLAG_REVOKED, &authkey->flags)) {
		key_put(authkey);
		authkey = ERR_PTR(-EKEYREVOKED);
	}

error:
	return authkey;
}