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
struct vcs_poll_data {int /*<<< orphan*/  notifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct vcs_poll_data*) ; 
 int /*<<< orphan*/  unregister_vt_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vcs_poll_data_free(struct vcs_poll_data *poll)
{
	unregister_vt_notifier(&poll->notifier);
	kfree(poll);
}