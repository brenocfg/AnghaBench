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
struct kernfs_open_file {int dummy; } ;
struct hugetlb_cgroup {int /*<<< orphan*/ * hugepage; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  private; } ;

/* Variables and functions */
 int EINVAL ; 
 int MEMFILE_ATTR (int /*<<< orphan*/ ) ; 
 int MEMFILE_IDX (int /*<<< orphan*/ ) ; 
#define  RES_LIMIT 128 
 int /*<<< orphan*/ * hstates ; 
 int huge_page_order (int /*<<< orphan*/ *) ; 
 struct hugetlb_cgroup* hugetlb_cgroup_from_css (int /*<<< orphan*/ ) ; 
 scalar_t__ hugetlb_cgroup_is_root (struct hugetlb_cgroup*) ; 
 int /*<<< orphan*/  hugetlb_limit_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* of_cft (struct kernfs_open_file*) ; 
 int /*<<< orphan*/  of_css (struct kernfs_open_file*) ; 
 int page_counter_memparse (char*,char*,unsigned long*) ; 
 int page_counter_set_max (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long round_down (unsigned long,int) ; 
 char* strstrip (char*) ; 

__attribute__((used)) static ssize_t hugetlb_cgroup_write(struct kernfs_open_file *of,
				    char *buf, size_t nbytes, loff_t off)
{
	int ret, idx;
	unsigned long nr_pages;
	struct hugetlb_cgroup *h_cg = hugetlb_cgroup_from_css(of_css(of));

	if (hugetlb_cgroup_is_root(h_cg)) /* Can't set limit on root */
		return -EINVAL;

	buf = strstrip(buf);
	ret = page_counter_memparse(buf, "-1", &nr_pages);
	if (ret)
		return ret;

	idx = MEMFILE_IDX(of_cft(of)->private);
	nr_pages = round_down(nr_pages, 1 << huge_page_order(&hstates[idx]));

	switch (MEMFILE_ATTR(of_cft(of)->private)) {
	case RES_LIMIT:
		mutex_lock(&hugetlb_limit_mutex);
		ret = page_counter_set_max(&h_cg->hugepage[idx], nr_pages);
		mutex_unlock(&hugetlb_limit_mutex);
		break;
	default:
		ret = -EINVAL;
		break;
	}
	return ret ?: nbytes;
}