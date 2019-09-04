#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mon_bus {TYPE_1__* classdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  devt; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mon_bin_class ; 

void mon_bin_del(struct mon_bus *mbus)
{
	device_destroy(mon_bin_class, mbus->classdev->devt);
}