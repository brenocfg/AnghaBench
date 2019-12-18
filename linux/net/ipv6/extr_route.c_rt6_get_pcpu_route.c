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
struct rt6_info {int dummy; } ;
struct fib6_result {TYPE_1__* nh; } ;
struct TYPE_2__ {int /*<<< orphan*/ * rt6i_pcpu; } ;

/* Variables and functions */
 struct rt6_info* this_cpu_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rt6_info *rt6_get_pcpu_route(const struct fib6_result *res)
{
	struct rt6_info *pcpu_rt;

	pcpu_rt = this_cpu_read(*res->nh->rt6i_pcpu);

	return pcpu_rt;
}