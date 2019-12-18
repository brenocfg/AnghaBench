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
struct mem_cgroup {int dummy; } ;
struct eventfd_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _MEM ; 
 int __mem_cgroup_usage_register_event (struct mem_cgroup*,struct eventfd_ctx*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mem_cgroup_usage_register_event(struct mem_cgroup *memcg,
	struct eventfd_ctx *eventfd, const char *args)
{
	return __mem_cgroup_usage_register_event(memcg, eventfd, args, _MEM);
}