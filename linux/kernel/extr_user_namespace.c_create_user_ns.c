#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * ops; } ;
struct user_namespace {int level; TYPE_1__ ns; int /*<<< orphan*/  persistent_keyring_register; int /*<<< orphan*/  keyring_sem; int /*<<< orphan*/  keyring_name_list; int /*<<< orphan*/  flags; struct ucounts* ucounts; int /*<<< orphan*/ * ucount_max; int /*<<< orphan*/  work; int /*<<< orphan*/  group; int /*<<< orphan*/  owner; struct user_namespace* parent; int /*<<< orphan*/  count; } ;
struct ucounts {int dummy; } ;
struct cred {int /*<<< orphan*/  egid; int /*<<< orphan*/  euid; struct user_namespace* user_ns; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT_MAX ; 
 int UCOUNT_COUNTS ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ current_chrooted () ; 
 int /*<<< orphan*/  dec_user_namespaces (struct ucounts*) ; 
 int /*<<< orphan*/  free_user_ns ; 
 struct ucounts* inc_user_namespaces (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kgid_has_mapping (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct user_namespace*) ; 
 struct user_namespace* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kuid_has_mapping (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ns_alloc_inum (TYPE_1__*) ; 
 int /*<<< orphan*/  ns_free_inum (TYPE_1__*) ; 
 int /*<<< orphan*/  set_cred_user_ns (struct cred*,struct user_namespace*) ; 
 int /*<<< orphan*/  setup_userns_sysctls (struct user_namespace*) ; 
 int /*<<< orphan*/  user_ns_cachep ; 
 int /*<<< orphan*/  userns_operations ; 
 int /*<<< orphan*/  userns_state_mutex ; 

int create_user_ns(struct cred *new)
{
	struct user_namespace *ns, *parent_ns = new->user_ns;
	kuid_t owner = new->euid;
	kgid_t group = new->egid;
	struct ucounts *ucounts;
	int ret, i;

	ret = -ENOSPC;
	if (parent_ns->level > 32)
		goto fail;

	ucounts = inc_user_namespaces(parent_ns, owner);
	if (!ucounts)
		goto fail;

	/*
	 * Verify that we can not violate the policy of which files
	 * may be accessed that is specified by the root directory,
	 * by verifing that the root directory is at the root of the
	 * mount namespace which allows all files to be accessed.
	 */
	ret = -EPERM;
	if (current_chrooted())
		goto fail_dec;

	/* The creator needs a mapping in the parent user namespace
	 * or else we won't be able to reasonably tell userspace who
	 * created a user_namespace.
	 */
	ret = -EPERM;
	if (!kuid_has_mapping(parent_ns, owner) ||
	    !kgid_has_mapping(parent_ns, group))
		goto fail_dec;

	ret = -ENOMEM;
	ns = kmem_cache_zalloc(user_ns_cachep, GFP_KERNEL);
	if (!ns)
		goto fail_dec;

	ret = ns_alloc_inum(&ns->ns);
	if (ret)
		goto fail_free;
	ns->ns.ops = &userns_operations;

	atomic_set(&ns->count, 1);
	/* Leave the new->user_ns reference with the new user namespace. */
	ns->parent = parent_ns;
	ns->level = parent_ns->level + 1;
	ns->owner = owner;
	ns->group = group;
	INIT_WORK(&ns->work, free_user_ns);
	for (i = 0; i < UCOUNT_COUNTS; i++) {
		ns->ucount_max[i] = INT_MAX;
	}
	ns->ucounts = ucounts;

	/* Inherit USERNS_SETGROUPS_ALLOWED from our parent */
	mutex_lock(&userns_state_mutex);
	ns->flags = parent_ns->flags;
	mutex_unlock(&userns_state_mutex);

#ifdef CONFIG_KEYS
	INIT_LIST_HEAD(&ns->keyring_name_list);
	init_rwsem(&ns->keyring_sem);
#endif
	ret = -ENOMEM;
	if (!setup_userns_sysctls(ns))
		goto fail_keyring;

	set_cred_user_ns(new, ns);
	return 0;
fail_keyring:
#ifdef CONFIG_PERSISTENT_KEYRINGS
	key_put(ns->persistent_keyring_register);
#endif
	ns_free_inum(&ns->ns);
fail_free:
	kmem_cache_free(user_ns_cachep, ns);
fail_dec:
	dec_user_namespaces(ucounts);
fail:
	return ret;
}