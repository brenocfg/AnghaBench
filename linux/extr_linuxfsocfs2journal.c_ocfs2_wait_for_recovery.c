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
struct ocfs2_super {int /*<<< orphan*/  recovery_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocfs2_recovery_completed (struct ocfs2_super*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ocfs2_wait_for_recovery(struct ocfs2_super *osb)
{
	wait_event(osb->recovery_event, ocfs2_recovery_completed(osb));
}