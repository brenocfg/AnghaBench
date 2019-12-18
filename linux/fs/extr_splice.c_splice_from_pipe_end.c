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
struct splice_desc {scalar_t__ need_wakeup; } ;
struct pipe_inode_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wakeup_pipe_writers (struct pipe_inode_info*) ; 

__attribute__((used)) static void splice_from_pipe_end(struct pipe_inode_info *pipe, struct splice_desc *sd)
{
	if (sd->need_wakeup)
		wakeup_pipe_writers(pipe);
}