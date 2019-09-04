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
struct TYPE_2__ {int /*<<< orphan*/ * type; } ;
struct keyring_search_context {TYPE_1__ index_key; } ;
struct key_user {int dummy; } ;
struct key {int dummy; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int ENOMEM ; 
 int EPERM ; 
 struct key* ERR_PTR (int) ; 
 int construct_alloc_key (struct keyring_search_context*,struct key*,unsigned long,struct key_user*,struct key**) ; 
 int construct_get_dest_keyring (struct key**) ; 
 int construct_key (struct key*,char const*,size_t,void*,struct key*) ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  kdebug (char*) ; 
 int /*<<< orphan*/  kenter (char*) ; 
 int /*<<< orphan*/  key_negate_and_link (struct key*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_negative_timeout ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int key_serial (struct key*) ; 
 int /*<<< orphan*/  key_type_keyring ; 
 struct key_user* key_user_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_user_put (struct key_user*) ; 
 int /*<<< orphan*/  kleave (char*,int) ; 

__attribute__((used)) static struct key *construct_key_and_link(struct keyring_search_context *ctx,
					  const char *callout_info,
					  size_t callout_len,
					  void *aux,
					  struct key *dest_keyring,
					  unsigned long flags)
{
	struct key_user *user;
	struct key *key;
	int ret;

	kenter("");

	if (ctx->index_key.type == &key_type_keyring)
		return ERR_PTR(-EPERM);

	ret = construct_get_dest_keyring(&dest_keyring);
	if (ret)
		goto error;

	user = key_user_lookup(current_fsuid());
	if (!user) {
		ret = -ENOMEM;
		goto error_put_dest_keyring;
	}

	ret = construct_alloc_key(ctx, dest_keyring, flags, user, &key);
	key_user_put(user);

	if (ret == 0) {
		ret = construct_key(key, callout_info, callout_len, aux,
				    dest_keyring);
		if (ret < 0) {
			kdebug("cons failed");
			goto construction_failed;
		}
	} else if (ret == -EINPROGRESS) {
		ret = 0;
	} else {
		goto error_put_dest_keyring;
	}

	key_put(dest_keyring);
	kleave(" = key %d", key_serial(key));
	return key;

construction_failed:
	key_negate_and_link(key, key_negative_timeout, NULL, NULL);
	key_put(key);
error_put_dest_keyring:
	key_put(dest_keyring);
error:
	kleave(" = %d", ret);
	return ERR_PTR(ret);
}