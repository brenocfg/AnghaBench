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
struct pipe_inode_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 int /*<<< orphan*/  pipe_lock_nested (struct pipe_inode_info*,int /*<<< orphan*/ ) ; 

void pipe_lock(struct pipe_inode_info *pipe)
{
	/*
	 * pipe_lock() nests non-pipe inode locks (for writing to a file)
	 */
	pipe_lock_nested(pipe, I_MUTEX_PARENT);
}