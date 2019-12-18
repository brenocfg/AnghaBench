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
struct pipe_inode_info {int /*<<< orphan*/  files; } ;
struct inode {int /*<<< orphan*/  i_lock; int /*<<< orphan*/ * i_pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_pipe_info (struct pipe_inode_info*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_pipe_info(struct inode *inode, struct pipe_inode_info *pipe)
{
	int kill = 0;

	spin_lock(&inode->i_lock);
	if (!--pipe->files) {
		inode->i_pipe = NULL;
		kill = 1;
	}
	spin_unlock(&inode->i_lock);

	if (kill)
		free_pipe_info(pipe);
}