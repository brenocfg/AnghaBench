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
typedef  int /*<<< orphan*/  umode_t ;
typedef  scalar_t__ u32 ;
struct kernfs_root {int /*<<< orphan*/  ino_idr; scalar_t__ next_generation; } ;
struct TYPE_2__ {int ino; scalar_t__ generation; } ;
struct kernfs_node {char const* name; unsigned int flags; TYPE_1__ id; int /*<<< orphan*/  mode; int /*<<< orphan*/  rb; int /*<<< orphan*/  active; int /*<<< orphan*/  count; } ;
struct iattr {int ia_valid; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int ATTR_GID ; 
 int ATTR_UID ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 int /*<<< orphan*/  KN_DEACTIVATED_BIAS ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int __kernfs_setattr (struct kernfs_node*,struct iattr*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set_release (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int idr_alloc_cyclic (int /*<<< orphan*/ *,struct kernfs_node*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int idr_get_cursor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kernfs_idr_lock ; 
 int /*<<< orphan*/  kernfs_node_cache ; 
 int /*<<< orphan*/  kfree_const (char const*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct kernfs_node*) ; 
 struct kernfs_node* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* kstrdup_const (char const*,int /*<<< orphan*/ ) ; 
 int security_kernfs_init_security (struct kernfs_node*,struct kernfs_node*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct kernfs_node *__kernfs_new_node(struct kernfs_root *root,
					     struct kernfs_node *parent,
					     const char *name, umode_t mode,
					     kuid_t uid, kgid_t gid,
					     unsigned flags)
{
	struct kernfs_node *kn;
	u32 gen;
	int cursor;
	int ret;

	name = kstrdup_const(name, GFP_KERNEL);
	if (!name)
		return NULL;

	kn = kmem_cache_zalloc(kernfs_node_cache, GFP_KERNEL);
	if (!kn)
		goto err_out1;

	idr_preload(GFP_KERNEL);
	spin_lock(&kernfs_idr_lock);
	cursor = idr_get_cursor(&root->ino_idr);
	ret = idr_alloc_cyclic(&root->ino_idr, kn, 1, 0, GFP_ATOMIC);
	if (ret >= 0 && ret < cursor)
		root->next_generation++;
	gen = root->next_generation;
	spin_unlock(&kernfs_idr_lock);
	idr_preload_end();
	if (ret < 0)
		goto err_out2;
	kn->id.ino = ret;
	kn->id.generation = gen;

	/*
	 * set ino first. This RELEASE is paired with atomic_inc_not_zero in
	 * kernfs_find_and_get_node_by_ino
	 */
	atomic_set_release(&kn->count, 1);
	atomic_set(&kn->active, KN_DEACTIVATED_BIAS);
	RB_CLEAR_NODE(&kn->rb);

	kn->name = name;
	kn->mode = mode;
	kn->flags = flags;

	if (!uid_eq(uid, GLOBAL_ROOT_UID) || !gid_eq(gid, GLOBAL_ROOT_GID)) {
		struct iattr iattr = {
			.ia_valid = ATTR_UID | ATTR_GID,
			.ia_uid = uid,
			.ia_gid = gid,
		};

		ret = __kernfs_setattr(kn, &iattr);
		if (ret < 0)
			goto err_out3;
	}

	if (parent) {
		ret = security_kernfs_init_security(parent, kn);
		if (ret)
			goto err_out3;
	}

	return kn;

 err_out3:
	idr_remove(&root->ino_idr, kn->id.ino);
 err_out2:
	kmem_cache_free(kernfs_node_cache, kn);
 err_out1:
	kfree_const(name);
	return NULL;
}