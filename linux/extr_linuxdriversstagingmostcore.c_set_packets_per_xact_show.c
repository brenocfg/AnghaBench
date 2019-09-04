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
struct TYPE_2__ {int packets_per_xact; } ;
struct most_channel {TYPE_1__ cfg; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 struct most_channel* to_channel (struct device*) ; 

__attribute__((used)) static ssize_t set_packets_per_xact_show(struct device *dev,
					 struct device_attribute *attr,
					 char *buf)
{
	struct most_channel *c = to_channel(dev);

	return snprintf(buf, PAGE_SIZE, "%d\n", c->cfg.packets_per_xact);
}