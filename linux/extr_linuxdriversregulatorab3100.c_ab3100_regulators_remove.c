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
struct platform_device {int dummy; } ;
struct ab3100_regulator {int /*<<< orphan*/ * rdev; } ;

/* Variables and functions */
 int AB3100_NUM_REGULATORS ; 
 struct ab3100_regulator* ab3100_regulators ; 

__attribute__((used)) static int ab3100_regulators_remove(struct platform_device *pdev)
{
	int i;

	for (i = 0; i < AB3100_NUM_REGULATORS; i++) {
		struct ab3100_regulator *reg = &ab3100_regulators[i];

		reg->rdev = NULL;
	}
	return 0;
}