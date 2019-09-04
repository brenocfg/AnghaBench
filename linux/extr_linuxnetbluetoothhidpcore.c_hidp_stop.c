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
struct hidp_session {int /*<<< orphan*/  intr_transmit; int /*<<< orphan*/  ctrl_transmit; } ;
struct hid_device {scalar_t__ claimed; struct hidp_session* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hidp_stop(struct hid_device *hid)
{
	struct hidp_session *session = hid->driver_data;

	skb_queue_purge(&session->ctrl_transmit);
	skb_queue_purge(&session->intr_transmit);

	hid->claimed = 0;
}