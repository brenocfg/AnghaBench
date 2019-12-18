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
struct page_counter {int /*<<< orphan*/  failcnt; } ;
struct kernfs_open_file {int dummy; } ;
struct hugetlb_cgroup {struct page_counter* hugepage; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  private; } ;

/* Variables and functions */
 int EINVAL ; 
 int MEMFILE_ATTR (int /*<<< orphan*/ ) ; 
 size_t MEMFILE_IDX (int /*<<< orphan*/ ) ; 
#define  RES_FAILCNT 129 
#define  RES_MAX_USAGE 128 
 struct hugetlb_cgroup* hugetlb_cgroup_from_css (int /*<<< orphan*/ ) ; 
 TYPE_1__* of_cft (struct kernfs_open_file*) ; 
 int /*<<< orphan*/  of_css (struct kernfs_open_file*) ; 
 int /*<<< orphan*/  page_counter_reset_watermark (struct page_counter*) ; 

__attribute__((used)) static ssize_t hugetlb_cgroup_reset(struct kernfs_open_file *of,
				    char *buf, size_t nbytes, loff_t off)
{
	int ret = 0;
	struct page_counter *counter;
	struct hugetlb_cgroup *h_cg = hugetlb_cgroup_from_css(of_css(of));

	counter = &h_cg->hugepage[MEMFILE_IDX(of_cft(of)->private)];

	switch (MEMFILE_ATTR(of_cft(of)->private)) {
	case RES_MAX_USAGE:
		page_counter_reset_watermark(counter);
		break;
	case RES_FAILCNT:
		counter->failcnt = 0;
		break;
	default:
		ret = -EINVAL;
		break;
	}
	return ret ?: nbytes;
}