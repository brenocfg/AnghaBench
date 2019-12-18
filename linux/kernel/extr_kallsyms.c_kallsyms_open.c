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
struct kallsym_iter {int /*<<< orphan*/  show_value; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct kallsym_iter* __seq_open_private (struct file*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kallsyms_op ; 
 int /*<<< orphan*/  kallsyms_show_value () ; 
 int /*<<< orphan*/  reset_iter (struct kallsym_iter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kallsyms_open(struct inode *inode, struct file *file)
{
	/*
	 * We keep iterator in m->private, since normal case is to
	 * s_start from where we left off, so we avoid doing
	 * using get_symbol_offset for every symbol.
	 */
	struct kallsym_iter *iter;
	iter = __seq_open_private(file, &kallsyms_op, sizeof(*iter));
	if (!iter)
		return -ENOMEM;
	reset_iter(iter, 0);

	iter->show_value = kallsyms_show_value();
	return 0;
}