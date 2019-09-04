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
struct stats_debug_info {int /*<<< orphan*/  i_private; } ;
struct inode {int /*<<< orphan*/  i_private; } ;
struct file {struct stats_debug_info* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct stats_debug_info* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fnic_reset_stats_open(struct inode *inode, struct file *file)
{
	struct stats_debug_info *debug;

	debug = kzalloc(sizeof(struct stats_debug_info), GFP_KERNEL);
	if (!debug)
		return -ENOMEM;

	debug->i_private = inode->i_private;

	file->private_data = debug;

	return 0;
}