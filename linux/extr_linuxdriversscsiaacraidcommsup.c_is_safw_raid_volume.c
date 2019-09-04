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
struct aac_dev {int maximum_num_containers; } ;

/* Variables and functions */
 int CONTAINER_CHANNEL ; 

__attribute__((used)) static inline int is_safw_raid_volume(struct aac_dev *aac, int bus, int target)
{
	return bus == CONTAINER_CHANNEL && target < aac->maximum_num_containers;
}