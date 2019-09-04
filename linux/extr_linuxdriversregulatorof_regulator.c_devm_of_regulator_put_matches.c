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
struct devm_of_regulator_matches {int num_matches; TYPE_1__* matches; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void devm_of_regulator_put_matches(struct device *dev, void *res)
{
	struct devm_of_regulator_matches *devm_matches = res;
	int i;

	for (i = 0; i < devm_matches->num_matches; i++)
		of_node_put(devm_matches->matches[i].of_node);
}