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
struct skl_dev {scalar_t__ dmic_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  platform_device_unregister (scalar_t__) ; 

__attribute__((used)) static void skl_dmic_device_unregister(struct skl_dev *skl)
{
	if (skl->dmic_dev)
		platform_device_unregister(skl->dmic_dev);
}