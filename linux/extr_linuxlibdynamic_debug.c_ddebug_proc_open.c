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
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct ddebug_iter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ddebug_proc_seqops ; 
 int seq_open_private (struct file*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vpr_info (char*) ; 

__attribute__((used)) static int ddebug_proc_open(struct inode *inode, struct file *file)
{
	vpr_info("called\n");
	return seq_open_private(file, &ddebug_proc_seqops,
				sizeof(struct ddebug_iter));
}