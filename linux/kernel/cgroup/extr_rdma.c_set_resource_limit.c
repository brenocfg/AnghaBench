#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rdmacg_resource_pool {TYPE_1__* resources; int /*<<< orphan*/  num_max_cnt; } ;
struct TYPE_2__ {int max; } ;

/* Variables and functions */
 int S32_MAX ; 

__attribute__((used)) static void set_resource_limit(struct rdmacg_resource_pool *rpool,
			       int index, int new_max)
{
	if (new_max == S32_MAX) {
		if (rpool->resources[index].max != S32_MAX)
			rpool->num_max_cnt++;
	} else {
		if (rpool->resources[index].max == S32_MAX)
			rpool->num_max_cnt--;
	}
	rpool->resources[index].max = new_max;
}