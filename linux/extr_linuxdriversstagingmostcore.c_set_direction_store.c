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
struct TYPE_2__ {void* direction; } ;
struct most_channel {TYPE_1__ cfg; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 void* MOST_CH_RX ; 
 void* MOST_CH_TX ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 struct most_channel* to_channel (struct device*) ; 

__attribute__((used)) static ssize_t set_direction_store(struct device *dev,
				   struct device_attribute *attr,
				   const char *buf,
				   size_t count)
{
	struct most_channel *c = to_channel(dev);

	if (!strcmp(buf, "dir_rx\n")) {
		c->cfg.direction = MOST_CH_RX;
	} else if (!strcmp(buf, "rx\n")) {
		c->cfg.direction = MOST_CH_RX;
	} else if (!strcmp(buf, "dir_tx\n")) {
		c->cfg.direction = MOST_CH_TX;
	} else if (!strcmp(buf, "tx\n")) {
		c->cfg.direction = MOST_CH_TX;
	} else {
		pr_info("WARN: invalid attribute settings\n");
		return -EINVAL;
	}
	return count;
}