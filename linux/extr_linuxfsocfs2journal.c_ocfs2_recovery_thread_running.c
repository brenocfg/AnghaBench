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
struct ocfs2_super {int /*<<< orphan*/ * recovery_thread_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static int ocfs2_recovery_thread_running(struct ocfs2_super *osb)
{
	mb();
	return osb->recovery_thread_task != NULL;
}