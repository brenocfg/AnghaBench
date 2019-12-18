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
struct proc_dir_entry {int mode; int /*<<< orphan*/  low_ino; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;
struct dir_context {int pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  dir_emit (struct dir_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dir_emit_dots (struct file*,struct dir_context*) ; 
 int /*<<< orphan*/  pde_get (struct proc_dir_entry*) ; 
 int /*<<< orphan*/  pde_put (struct proc_dir_entry*) ; 
 struct proc_dir_entry* pde_subdir_first (struct proc_dir_entry*) ; 
 struct proc_dir_entry* pde_subdir_next (struct proc_dir_entry*) ; 
 int /*<<< orphan*/  proc_subdir_lock ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

int proc_readdir_de(struct file *file, struct dir_context *ctx,
		    struct proc_dir_entry *de)
{
	int i;

	if (!dir_emit_dots(file, ctx))
		return 0;

	i = ctx->pos - 2;
	read_lock(&proc_subdir_lock);
	de = pde_subdir_first(de);
	for (;;) {
		if (!de) {
			read_unlock(&proc_subdir_lock);
			return 0;
		}
		if (!i)
			break;
		de = pde_subdir_next(de);
		i--;
	}

	do {
		struct proc_dir_entry *next;
		pde_get(de);
		read_unlock(&proc_subdir_lock);
		if (!dir_emit(ctx, de->name, de->namelen,
			    de->low_ino, de->mode >> 12)) {
			pde_put(de);
			return 0;
		}
		ctx->pos++;
		read_lock(&proc_subdir_lock);
		next = pde_subdir_next(de);
		pde_put(de);
		de = next;
	} while (de);
	read_unlock(&proc_subdir_lock);
	return 1;
}