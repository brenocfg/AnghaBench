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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct nhlt_endpoint {scalar_t__ virtual_bus_id; scalar_t__ linktype; scalar_t__ direction; scalar_t__ device_type; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ NHLT_LINK_DMIC ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool skl_check_ep_match(struct device *dev, struct nhlt_endpoint *epnt,
		u32 instance_id, u8 link_type, u8 dirn, u8 dev_type)
{
	dev_dbg(dev, "vbus_id=%d link_type=%d dir=%d dev_type = %d\n",
			epnt->virtual_bus_id, epnt->linktype,
			epnt->direction, epnt->device_type);

	if ((epnt->virtual_bus_id == instance_id) &&
			(epnt->linktype == link_type) &&
			(epnt->direction == dirn)) {
		/* do not check dev_type for DMIC link type */
		if (epnt->linktype == NHLT_LINK_DMIC)
			return true;

		if (epnt->device_type == dev_type)
			return true;
	}

	return false;
}