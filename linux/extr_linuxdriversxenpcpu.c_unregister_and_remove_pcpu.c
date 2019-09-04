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
struct device {int dummy; } ;
struct pcpu {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (struct device*) ; 

__attribute__((used)) static void unregister_and_remove_pcpu(struct pcpu *pcpu)
{
	struct device *dev;

	if (!pcpu)
		return;

	dev = &pcpu->dev;
	/* pcpu remove would be implicitly done */
	device_unregister(dev);
}