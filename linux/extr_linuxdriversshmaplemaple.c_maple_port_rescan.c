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
struct maple_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAPLE_COMMAND_DEVINFO ; 
 int MAPLE_PORTS ; 
 struct maple_device** baseunits ; 
 int* checked ; 
 int fullscan ; 
 int /*<<< orphan*/  maple_add_packet (struct maple_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void maple_port_rescan(void)
{
	int i;
	struct maple_device *mdev;

	fullscan = 1;
	for (i = 0; i < MAPLE_PORTS; i++) {
		if (checked[i] == false) {
			fullscan = 0;
			mdev = baseunits[i];
			maple_add_packet(mdev, 0, MAPLE_COMMAND_DEVINFO,
				0, NULL);
		}
	}
}