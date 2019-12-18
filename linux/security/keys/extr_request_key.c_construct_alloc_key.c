#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  description; TYPE_1__* type; } ;
struct keyring_search_context {TYPE_4__ index_key; TYPE_3__* cred; } ;
struct key_user {int /*<<< orphan*/  cons_lock; } ;
struct key {int /*<<< orphan*/  flags; } ;
struct assoc_array_edit {int dummy; } ;
typedef  struct key* key_ref_t ;
typedef  int key_perm_t ;
struct TYPE_8__ {int /*<<< orphan*/  fsgid; int /*<<< orphan*/  fsuid; } ;
struct TYPE_7__ {scalar_t__ update; scalar_t__ read; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int /*<<< orphan*/  KEY_FLAG_USER_CONSTRUCT ; 
 int KEY_POS_LINK ; 
 int KEY_POS_READ ; 
 int KEY_POS_SEARCH ; 
 int KEY_POS_SETATTR ; 
 int KEY_POS_VIEW ; 
 int KEY_POS_WRITE ; 
 int KEY_USR_VIEW ; 
 int PTR_ERR (struct key*) ; 
 int /*<<< orphan*/  __key_link (struct key*,struct assoc_array_edit**) ; 
 int __key_link_begin (struct key*,TYPE_4__*,struct assoc_array_edit**) ; 
 int __key_link_check_live_key (struct key*,struct key*) ; 
 int /*<<< orphan*/  __key_link_end (struct key*,TYPE_4__*,struct assoc_array_edit*) ; 
 int __key_link_lock (struct key*,TYPE_4__*) ; 
 int /*<<< orphan*/  kenter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct key* key_alloc (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_construction_mutex ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 struct key* key_ref_to_ptr (struct key*) ; 
 int key_serial (struct key*) ; 
 TYPE_1__ key_type_keyring ; 
 int /*<<< orphan*/  kleave (char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct key* search_process_keyrings_rcu (struct keyring_search_context*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int construct_alloc_key(struct keyring_search_context *ctx,
			       struct key *dest_keyring,
			       unsigned long flags,
			       struct key_user *user,
			       struct key **_key)
{
	struct assoc_array_edit *edit = NULL;
	struct key *key;
	key_perm_t perm;
	key_ref_t key_ref;
	int ret;

	kenter("%s,%s,,,",
	       ctx->index_key.type->name, ctx->index_key.description);

	*_key = NULL;
	mutex_lock(&user->cons_lock);

	perm = KEY_POS_VIEW | KEY_POS_SEARCH | KEY_POS_LINK | KEY_POS_SETATTR;
	perm |= KEY_USR_VIEW;
	if (ctx->index_key.type->read)
		perm |= KEY_POS_READ;
	if (ctx->index_key.type == &key_type_keyring ||
	    ctx->index_key.type->update)
		perm |= KEY_POS_WRITE;

	key = key_alloc(ctx->index_key.type, ctx->index_key.description,
			ctx->cred->fsuid, ctx->cred->fsgid, ctx->cred,
			perm, flags, NULL);
	if (IS_ERR(key))
		goto alloc_failed;

	set_bit(KEY_FLAG_USER_CONSTRUCT, &key->flags);

	if (dest_keyring) {
		ret = __key_link_lock(dest_keyring, &ctx->index_key);
		if (ret < 0)
			goto link_lock_failed;
		ret = __key_link_begin(dest_keyring, &ctx->index_key, &edit);
		if (ret < 0)
			goto link_prealloc_failed;
	}

	/* attach the key to the destination keyring under lock, but we do need
	 * to do another check just in case someone beat us to it whilst we
	 * waited for locks */
	mutex_lock(&key_construction_mutex);

	rcu_read_lock();
	key_ref = search_process_keyrings_rcu(ctx);
	rcu_read_unlock();
	if (!IS_ERR(key_ref))
		goto key_already_present;

	if (dest_keyring)
		__key_link(key, &edit);

	mutex_unlock(&key_construction_mutex);
	if (dest_keyring)
		__key_link_end(dest_keyring, &ctx->index_key, edit);
	mutex_unlock(&user->cons_lock);
	*_key = key;
	kleave(" = 0 [%d]", key_serial(key));
	return 0;

	/* the key is now present - we tell the caller that we found it by
	 * returning -EINPROGRESS  */
key_already_present:
	key_put(key);
	mutex_unlock(&key_construction_mutex);
	key = key_ref_to_ptr(key_ref);
	if (dest_keyring) {
		ret = __key_link_check_live_key(dest_keyring, key);
		if (ret == 0)
			__key_link(key, &edit);
		__key_link_end(dest_keyring, &ctx->index_key, edit);
		if (ret < 0)
			goto link_check_failed;
	}
	mutex_unlock(&user->cons_lock);
	*_key = key;
	kleave(" = -EINPROGRESS [%d]", key_serial(key));
	return -EINPROGRESS;

link_check_failed:
	mutex_unlock(&user->cons_lock);
	key_put(key);
	kleave(" = %d [linkcheck]", ret);
	return ret;

link_prealloc_failed:
	__key_link_end(dest_keyring, &ctx->index_key, edit);
link_lock_failed:
	mutex_unlock(&user->cons_lock);
	key_put(key);
	kleave(" = %d [prelink]", ret);
	return ret;

alloc_failed:
	mutex_unlock(&user->cons_lock);
	kleave(" = %ld", PTR_ERR(key));
	return PTR_ERR(key);
}