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
struct iwl_rx_packet {int dummy; } ;
struct iwl_notif_wait_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_notification_notify (struct iwl_notif_wait_data*) ; 
 scalar_t__ iwl_notification_wait (struct iwl_notif_wait_data*,struct iwl_rx_packet*) ; 

__attribute__((used)) static inline void
iwl_notification_wait_notify(struct iwl_notif_wait_data *notif_data,
			     struct iwl_rx_packet *pkt)
{
	if (iwl_notification_wait(notif_data, pkt))
		iwl_notification_notify(notif_data);
}