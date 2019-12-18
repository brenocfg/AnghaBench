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
struct rdmacg_resource_pool {int dummy; } ;

/* Variables and functions */
 int RDMACG_RESOURCE_MAX ; 
 int /*<<< orphan*/  S32_MAX ; 
 int /*<<< orphan*/  set_resource_limit (struct rdmacg_resource_pool*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_all_resource_max_limit(struct rdmacg_resource_pool *rpool)
{
	int i;

	for (i = 0; i < RDMACG_RESOURCE_MAX; i++)
		set_resource_limit(rpool, i, S32_MAX);
}