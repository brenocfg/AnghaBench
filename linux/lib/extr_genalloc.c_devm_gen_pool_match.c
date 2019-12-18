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
struct gen_pool {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int devm_gen_pool_match(struct device *dev, void *res, void *data)
{
	struct gen_pool **p = res;

	/* NULL data matches only a pool without an assigned name */
	if (!data && !(*p)->name)
		return 1;

	if (!data || !(*p)->name)
		return 0;

	return !strcmp((*p)->name, data);
}