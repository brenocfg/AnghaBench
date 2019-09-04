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
struct proc_dir_entry {int /*<<< orphan*/  pde_unload_lock; int /*<<< orphan*/  pde_openers; TYPE_1__* proc_fops; } ;
struct pde_opener {int closing; int /*<<< orphan*/  lh; int /*<<< orphan*/ * c; struct file* file; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int (* release ) (struct inode*,struct file*) ;int (* open ) (struct inode*,struct file*) ;} ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct proc_dir_entry* PDE (struct inode*) ; 
 struct pde_opener* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct pde_opener*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pde_opener_cache ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unuse_pde (struct proc_dir_entry*) ; 
 int /*<<< orphan*/  use_pde (struct proc_dir_entry*) ; 

__attribute__((used)) static int proc_reg_open(struct inode *inode, struct file *file)
{
	struct proc_dir_entry *pde = PDE(inode);
	int rv = 0;
	int (*open)(struct inode *, struct file *);
	int (*release)(struct inode *, struct file *);
	struct pde_opener *pdeo;

	/*
	 * Ensure that
	 * 1) PDE's ->release hook will be called no matter what
	 *    either normally by close()/->release, or forcefully by
	 *    rmmod/remove_proc_entry.
	 *
	 * 2) rmmod isn't blocked by opening file in /proc and sitting on
	 *    the descriptor (including "rmmod foo </proc/foo" scenario).
	 *
	 * Save every "struct file" with custom ->release hook.
	 */
	if (!use_pde(pde))
		return -ENOENT;

	release = pde->proc_fops->release;
	if (release) {
		pdeo = kmem_cache_alloc(pde_opener_cache, GFP_KERNEL);
		if (!pdeo) {
			rv = -ENOMEM;
			goto out_unuse;
		}
	}

	open = pde->proc_fops->open;
	if (open)
		rv = open(inode, file);

	if (release) {
		if (rv == 0) {
			/* To know what to release. */
			pdeo->file = file;
			pdeo->closing = false;
			pdeo->c = NULL;
			spin_lock(&pde->pde_unload_lock);
			list_add(&pdeo->lh, &pde->pde_openers);
			spin_unlock(&pde->pde_unload_lock);
		} else
			kmem_cache_free(pde_opener_cache, pdeo);
	}

out_unuse:
	unuse_pde(pde);
	return rv;
}