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
struct uprobe_consumer {int dummy; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int __uprobe_register (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uprobe_consumer*) ; 

int uprobe_register(struct inode *inode, loff_t offset,
		    struct uprobe_consumer *uc)
{
	return __uprobe_register(inode, offset, 0, uc);
}