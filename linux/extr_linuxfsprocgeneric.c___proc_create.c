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
typedef  int /*<<< orphan*/  umode_t ;
struct qstr {char const* name; int len; } ;
struct proc_dir_entry {int namelen; int /*<<< orphan*/ * proc_dops; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  pde_openers; int /*<<< orphan*/  pde_unload_lock; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  subdir; int /*<<< orphan*/  nlink; int /*<<< orphan*/  mode; int /*<<< orphan*/  name; int /*<<< orphan*/  inline_name; } ;
typedef  int /*<<< orphan*/  nlink_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int SIZEOF_PDE_INLINE_NAME ; 
 int /*<<< orphan*/  WARN (int,char*,...) ; 
 scalar_t__ is_empty_pde (struct proc_dir_entry*) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 struct proc_dir_entry* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 unsigned int name_to_int (struct qstr*) ; 
 int /*<<< orphan*/  pde_free (struct proc_dir_entry*) ; 
 int /*<<< orphan*/  proc_dir_entry_cache ; 
 int /*<<< orphan*/  proc_misc_dentry_ops ; 
 struct proc_dir_entry proc_root ; 
 int /*<<< orphan*/  proc_set_user (struct proc_dir_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 scalar_t__ xlate_proc_name (char const*,struct proc_dir_entry**,char const**) ; 

__attribute__((used)) static struct proc_dir_entry *__proc_create(struct proc_dir_entry **parent,
					  const char *name,
					  umode_t mode,
					  nlink_t nlink)
{
	struct proc_dir_entry *ent = NULL;
	const char *fn;
	struct qstr qstr;

	if (xlate_proc_name(name, parent, &fn) != 0)
		goto out;
	qstr.name = fn;
	qstr.len = strlen(fn);
	if (qstr.len == 0 || qstr.len >= 256) {
		WARN(1, "name len %u\n", qstr.len);
		return NULL;
	}
	if (qstr.len == 1 && fn[0] == '.') {
		WARN(1, "name '.'\n");
		return NULL;
	}
	if (qstr.len == 2 && fn[0] == '.' && fn[1] == '.') {
		WARN(1, "name '..'\n");
		return NULL;
	}
	if (*parent == &proc_root && name_to_int(&qstr) != ~0U) {
		WARN(1, "create '/proc/%s' by hand\n", qstr.name);
		return NULL;
	}
	if (is_empty_pde(*parent)) {
		WARN(1, "attempt to add to permanently empty directory");
		return NULL;
	}

	ent = kmem_cache_zalloc(proc_dir_entry_cache, GFP_KERNEL);
	if (!ent)
		goto out;

	if (qstr.len + 1 <= SIZEOF_PDE_INLINE_NAME) {
		ent->name = ent->inline_name;
	} else {
		ent->name = kmalloc(qstr.len + 1, GFP_KERNEL);
		if (!ent->name) {
			pde_free(ent);
			return NULL;
		}
	}

	memcpy(ent->name, fn, qstr.len + 1);
	ent->namelen = qstr.len;
	ent->mode = mode;
	ent->nlink = nlink;
	ent->subdir = RB_ROOT;
	refcount_set(&ent->refcnt, 1);
	spin_lock_init(&ent->pde_unload_lock);
	INIT_LIST_HEAD(&ent->pde_openers);
	proc_set_user(ent, (*parent)->uid, (*parent)->gid);

	ent->proc_dops = &proc_misc_dentry_ops;

out:
	return ent;
}