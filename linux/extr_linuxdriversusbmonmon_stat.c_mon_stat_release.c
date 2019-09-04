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
struct snap {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct snap* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snap*) ; 

__attribute__((used)) static int mon_stat_release(struct inode *inode, struct file *file)
{
	struct snap *sp = file->private_data;
	file->private_data = NULL;
	kfree(sp);
	return 0;
}