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
struct viafb_dev {int dummy; } ;

/* Variables and functions */
 int N_SUBDEVS ; 
 int /*<<< orphan*/  via_create_subdev (struct viafb_dev*,scalar_t__) ; 
 scalar_t__ viafb_subdevs ; 

__attribute__((used)) static int via_setup_subdevs(struct viafb_dev *vdev)
{
	int i;

	/*
	 * Ignore return values.  Even if some of the devices
	 * fail to be created, we'll still be able to use some
	 * of the rest.
	 */
	for (i = 0; i < N_SUBDEVS; i++)
		via_create_subdev(vdev, viafb_subdevs + i);
	return 0;
}