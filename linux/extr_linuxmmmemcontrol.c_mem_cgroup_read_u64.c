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
typedef  int u64 ;
struct page_counter {int failcnt; int /*<<< orphan*/  watermark; int /*<<< orphan*/  max; } ;
struct mem_cgroup {int /*<<< orphan*/  soft_limit; struct page_counter memsw; struct page_counter memory; struct page_counter tcpmem; struct page_counter kmem; } ;
struct cgroup_subsys_state {int dummy; } ;
struct cftype {int /*<<< orphan*/  private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int MEMFILE_ATTR (int /*<<< orphan*/ ) ; 
 int MEMFILE_TYPE (int /*<<< orphan*/ ) ; 
 int PAGE_SIZE ; 
#define  RES_FAILCNT 136 
#define  RES_LIMIT 135 
#define  RES_MAX_USAGE 134 
#define  RES_SOFT_LIMIT 133 
#define  RES_USAGE 132 
#define  _KMEM 131 
#define  _MEM 130 
#define  _MEMSWAP 129 
#define  _TCP 128 
 struct mem_cgroup* mem_cgroup_from_css (struct cgroup_subsys_state*) ; 
 int /*<<< orphan*/  mem_cgroup_usage (struct mem_cgroup*,int) ; 
 int /*<<< orphan*/  page_counter_read (struct page_counter*) ; 

__attribute__((used)) static u64 mem_cgroup_read_u64(struct cgroup_subsys_state *css,
			       struct cftype *cft)
{
	struct mem_cgroup *memcg = mem_cgroup_from_css(css);
	struct page_counter *counter;

	switch (MEMFILE_TYPE(cft->private)) {
	case _MEM:
		counter = &memcg->memory;
		break;
	case _MEMSWAP:
		counter = &memcg->memsw;
		break;
	case _KMEM:
		counter = &memcg->kmem;
		break;
	case _TCP:
		counter = &memcg->tcpmem;
		break;
	default:
		BUG();
	}

	switch (MEMFILE_ATTR(cft->private)) {
	case RES_USAGE:
		if (counter == &memcg->memory)
			return (u64)mem_cgroup_usage(memcg, false) * PAGE_SIZE;
		if (counter == &memcg->memsw)
			return (u64)mem_cgroup_usage(memcg, true) * PAGE_SIZE;
		return (u64)page_counter_read(counter) * PAGE_SIZE;
	case RES_LIMIT:
		return (u64)counter->max * PAGE_SIZE;
	case RES_MAX_USAGE:
		return (u64)counter->watermark * PAGE_SIZE;
	case RES_FAILCNT:
		return counter->failcnt;
	case RES_SOFT_LIMIT:
		return (u64)memcg->soft_limit * PAGE_SIZE;
	default:
		BUG();
	}
}