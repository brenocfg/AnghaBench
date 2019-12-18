#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  filter; } ;
struct TYPE_4__ {int /*<<< orphan*/  dentry; } ;
struct trace_uprobe {int /*<<< orphan*/ * inode; TYPE_2__ consumer; int /*<<< orphan*/  offset; scalar_t__ ref_ctr_offset; TYPE_1__ path; } ;
typedef  int /*<<< orphan*/  filter_func_t ;

/* Variables and functions */
 int /*<<< orphan*/ * d_real_inode (int /*<<< orphan*/ ) ; 
 int uprobe_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int uprobe_register_refctr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,TYPE_2__*) ; 

__attribute__((used)) static int trace_uprobe_enable(struct trace_uprobe *tu, filter_func_t filter)
{
	int ret;

	tu->consumer.filter = filter;
	tu->inode = d_real_inode(tu->path.dentry);

	if (tu->ref_ctr_offset)
		ret = uprobe_register_refctr(tu->inode, tu->offset,
				tu->ref_ctr_offset, &tu->consumer);
	else
		ret = uprobe_register(tu->inode, tu->offset, &tu->consumer);

	if (ret)
		tu->inode = NULL;

	return ret;
}