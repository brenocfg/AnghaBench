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
struct inode {struct debugfs_devm_entry* i_private; } ;
struct file {int dummy; } ;
struct debugfs_devm_entry {int /*<<< orphan*/  dev; int /*<<< orphan*/  read; } ;

/* Variables and functions */
 int single_open (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int debugfs_devm_entry_open(struct inode *inode, struct file *f)
{
	struct debugfs_devm_entry *entry = inode->i_private;

	return single_open(f, entry->read, entry->dev);
}