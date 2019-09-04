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
struct hugetlb_cgroup {struct page_counter* hugepage; } ;
struct cgroup_subsys_state {int dummy; } ;
struct cftype {int /*<<< orphan*/  private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int MEMFILE_ATTR (int /*<<< orphan*/ ) ; 
 size_t MEMFILE_IDX (int /*<<< orphan*/ ) ; 
 int PAGE_SIZE ; 
#define  RES_FAILCNT 131 
#define  RES_LIMIT 130 
#define  RES_MAX_USAGE 129 
#define  RES_USAGE 128 
 struct hugetlb_cgroup* hugetlb_cgroup_from_css (struct cgroup_subsys_state*) ; 
 int /*<<< orphan*/  page_counter_read (struct page_counter*) ; 

__attribute__((used)) static u64 hugetlb_cgroup_read_u64(struct cgroup_subsys_state *css,
				   struct cftype *cft)
{
	struct page_counter *counter;
	struct hugetlb_cgroup *h_cg = hugetlb_cgroup_from_css(css);

	counter = &h_cg->hugepage[MEMFILE_IDX(cft->private)];

	switch (MEMFILE_ATTR(cft->private)) {
	case RES_USAGE:
		return (u64)page_counter_read(counter) * PAGE_SIZE;
	case RES_LIMIT:
		return (u64)counter->max * PAGE_SIZE;
	case RES_MAX_USAGE:
		return (u64)counter->watermark * PAGE_SIZE;
	case RES_FAILCNT:
		return counter->failcnt;
	default:
		BUG();
	}
}