#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  chip ; 
 int /*<<< orphan*/  dev_err (struct device const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flexfb_chip_load_param (TYPE_1__*) ; 
 TYPE_1__* flexfb_chip_table ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int flexfb_chip_init(const struct device *dev)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(flexfb_chip_table); i++)
		if (!strcmp(chip, flexfb_chip_table[i].name)) {
			flexfb_chip_load_param(&flexfb_chip_table[i]);
			return 0;
		}

	dev_err(dev, "chip=%s is not supported\n", chip);

	return -EINVAL;
}