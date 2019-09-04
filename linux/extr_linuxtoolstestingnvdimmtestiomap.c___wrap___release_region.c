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
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  __release_region (struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfit_test_release_region (int /*<<< orphan*/ *,struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void __wrap___release_region(struct resource *parent, resource_size_t start,
		resource_size_t n)
{
	if (!nfit_test_release_region(NULL, parent, start, n))
		__release_region(parent, start, n);
}