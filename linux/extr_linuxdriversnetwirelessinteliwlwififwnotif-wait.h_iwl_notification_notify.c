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
struct iwl_notif_wait_data {int /*<<< orphan*/  notif_waitq; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
iwl_notification_notify(struct iwl_notif_wait_data *notif_data)
{
	wake_up_all(&notif_data->notif_waitq);
}