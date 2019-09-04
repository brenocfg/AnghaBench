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
struct pipe_inode_info {int /*<<< orphan*/  mutex; scalar_t__ files; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void pipe_lock_nested(struct pipe_inode_info *pipe, int subclass)
{
	if (pipe->files)
		mutex_lock_nested(&pipe->mutex, subclass);
}