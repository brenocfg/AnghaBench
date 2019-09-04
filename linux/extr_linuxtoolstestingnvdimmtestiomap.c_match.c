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
struct resource {scalar_t__ start; } ;
struct device {int dummy; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */

__attribute__((used)) static int match(struct device *dev, void *__res, void *match_data)
{
	struct resource *res = *((struct resource **) __res);
	resource_size_t start = *((resource_size_t *) match_data);

	return res->start == start;
}