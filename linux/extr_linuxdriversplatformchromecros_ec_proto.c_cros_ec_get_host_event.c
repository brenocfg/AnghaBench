#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  host_event; } ;
struct TYPE_4__ {scalar_t__ event_type; TYPE_1__ data; } ;
struct cros_ec_device {int event_size; TYPE_2__ event_data; int /*<<< orphan*/  dev; int /*<<< orphan*/  mkbp_event_supported; } ;
typedef  int /*<<< orphan*/  host_event ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ EC_MKBP_EVENT_HOST_EVENT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_unaligned_le32 (int /*<<< orphan*/ *) ; 

u32 cros_ec_get_host_event(struct cros_ec_device *ec_dev)
{
	u32 host_event;

	BUG_ON(!ec_dev->mkbp_event_supported);

	if (ec_dev->event_data.event_type != EC_MKBP_EVENT_HOST_EVENT)
		return 0;

	if (ec_dev->event_size != sizeof(host_event)) {
		dev_warn(ec_dev->dev, "Invalid host event size\n");
		return 0;
	}

	host_event = get_unaligned_le32(&ec_dev->event_data.data.host_event);

	return host_event;
}