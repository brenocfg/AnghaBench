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
struct region_devres {int /*<<< orphan*/  n; int /*<<< orphan*/  start; int /*<<< orphan*/  parent; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void devm_region_release(struct device *dev, void *res)
{
	struct region_devres *this = res;

	__release_region(this->parent, this->start, this->n);
}