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
struct resource {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 scalar_t__ get_nfit_res (int /*<<< orphan*/ ) ; 
 int remove_resource (struct resource*) ; 

int __wrap_remove_resource(struct resource *res)
{
	if (get_nfit_res(res->start))
		return 0;
	return remove_resource(res);
}