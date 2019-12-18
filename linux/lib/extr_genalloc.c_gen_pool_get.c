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
struct gen_pool {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_gen_pool_match ; 
 int /*<<< orphan*/  devm_gen_pool_release ; 
 struct gen_pool** devres_find (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

struct gen_pool *gen_pool_get(struct device *dev, const char *name)
{
	struct gen_pool **p;

	p = devres_find(dev, devm_gen_pool_release, devm_gen_pool_match,
			(void *)name);
	if (!p)
		return NULL;
	return *p;
}