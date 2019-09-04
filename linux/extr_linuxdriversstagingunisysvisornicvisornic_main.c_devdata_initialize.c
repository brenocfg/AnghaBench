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
struct visornic_devdata {int /*<<< orphan*/  incarnation_id; struct visor_device* dev; } ;
struct visor_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_jiffies_64 () ; 

__attribute__((used)) static struct visornic_devdata *devdata_initialize(
					struct visornic_devdata *devdata,
					struct visor_device *dev)
{
	devdata->dev = dev;
	devdata->incarnation_id = get_jiffies_64();
	return devdata;
}