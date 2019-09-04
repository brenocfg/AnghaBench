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
 int insert_resource (struct resource*,struct resource*) ; 

int __wrap_insert_resource(struct resource *parent, struct resource *res)
{
	if (get_nfit_res(res->start))
		return 0;
	return insert_resource(parent, res);
}