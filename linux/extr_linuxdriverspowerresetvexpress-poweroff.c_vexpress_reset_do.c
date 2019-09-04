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
struct regmap {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  dev_emerg (struct device*,char*,char const*,int) ; 
 struct regmap* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vexpress_reset_do(struct device *dev, const char *what)
{
	int err = -ENOENT;
	struct regmap *reg = dev_get_drvdata(dev);

	if (reg) {
		err = regmap_write(reg, 0, 0);
		if (!err)
			mdelay(1000);
	}

	dev_emerg(dev, "Unable to %s (%d)\n", what, err);
}