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
struct rcar_gen3_chan {TYPE_1__* phy; int /*<<< orphan*/  has_otg_pins; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  init_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 struct rcar_gen3_chan* dev_get_drvdata (struct device*) ; 
 scalar_t__ rcar_gen3_is_host (struct rcar_gen3_chan*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t role_show(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	struct rcar_gen3_chan *ch = dev_get_drvdata(dev);

	if (!ch->has_otg_pins || !ch->phy->init_count)
		return -EIO;

	return sprintf(buf, "%s\n", rcar_gen3_is_host(ch) ? "host" :
							    "peripheral");
}