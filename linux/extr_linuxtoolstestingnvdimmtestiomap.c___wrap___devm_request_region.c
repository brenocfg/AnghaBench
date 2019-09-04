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
struct resource {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 struct resource* nfit_test_request_region (struct device*,struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

struct resource *__wrap___devm_request_region(struct device *dev,
		struct resource *parent, resource_size_t start,
		resource_size_t n, const char *name)
{
	if (!dev)
		return NULL;
	return nfit_test_request_region(dev, parent, start, n, name, 0);
}