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
struct platform_device {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/  init_data; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 TYPE_1__* db8500_regulator_matches ; 
 int db8500_regulator_register (struct platform_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbx500_regulator_info ; 

__attribute__((used)) static int
db8500_regulator_of_probe(struct platform_device *pdev,
			struct device_node *np)
{
	int i, err;

	for (i = 0; i < ARRAY_SIZE(dbx500_regulator_info); i++) {
		err = db8500_regulator_register(
			pdev, db8500_regulator_matches[i].init_data,
			i, db8500_regulator_matches[i].of_node);
		if (err)
			return err;
	}

	return 0;
}