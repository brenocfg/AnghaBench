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
struct regulator_bulk_devres {int /*<<< orphan*/  consumers; int /*<<< orphan*/  num_consumers; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  regulator_bulk_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void devm_regulator_bulk_release(struct device *dev, void *res)
{
	struct regulator_bulk_devres *devres = res;

	regulator_bulk_free(devres->num_consumers, devres->consumers);
}