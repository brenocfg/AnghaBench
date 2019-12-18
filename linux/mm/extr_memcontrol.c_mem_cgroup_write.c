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
struct mem_cgroup {unsigned long soft_limit; } ;
struct kernfs_open_file {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  private; } ;

/* Variables and functions */
 int EINVAL ; 
 int MEMFILE_ATTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMFILE_TYPE (int /*<<< orphan*/ ) ; 
#define  RES_LIMIT 133 
#define  RES_SOFT_LIMIT 132 
#define  _KMEM 131 
#define  _MEM 130 
#define  _MEMSWAP 129 
#define  _TCP 128 
 struct mem_cgroup* mem_cgroup_from_css (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_cgroup_is_root (struct mem_cgroup*) ; 
 int mem_cgroup_resize_max (struct mem_cgroup*,unsigned long,int) ; 
 int memcg_update_kmem_max (struct mem_cgroup*,unsigned long) ; 
 int memcg_update_tcp_max (struct mem_cgroup*,unsigned long) ; 
 TYPE_1__* of_cft (struct kernfs_open_file*) ; 
 int /*<<< orphan*/  of_css (struct kernfs_open_file*) ; 
 int page_counter_memparse (char*,char*,unsigned long*) ; 
 int /*<<< orphan*/  pr_warn_once (char*) ; 
 char* strstrip (char*) ; 

__attribute__((used)) static ssize_t mem_cgroup_write(struct kernfs_open_file *of,
				char *buf, size_t nbytes, loff_t off)
{
	struct mem_cgroup *memcg = mem_cgroup_from_css(of_css(of));
	unsigned long nr_pages;
	int ret;

	buf = strstrip(buf);
	ret = page_counter_memparse(buf, "-1", &nr_pages);
	if (ret)
		return ret;

	switch (MEMFILE_ATTR(of_cft(of)->private)) {
	case RES_LIMIT:
		if (mem_cgroup_is_root(memcg)) { /* Can't set limit on root */
			ret = -EINVAL;
			break;
		}
		switch (MEMFILE_TYPE(of_cft(of)->private)) {
		case _MEM:
			ret = mem_cgroup_resize_max(memcg, nr_pages, false);
			break;
		case _MEMSWAP:
			ret = mem_cgroup_resize_max(memcg, nr_pages, true);
			break;
		case _KMEM:
			pr_warn_once("kmem.limit_in_bytes is deprecated and will be removed. "
				     "Please report your usecase to linux-mm@kvack.org if you "
				     "depend on this functionality.\n");
			ret = memcg_update_kmem_max(memcg, nr_pages);
			break;
		case _TCP:
			ret = memcg_update_tcp_max(memcg, nr_pages);
			break;
		}
		break;
	case RES_SOFT_LIMIT:
		memcg->soft_limit = nr_pages;
		ret = 0;
		break;
	}
	return ret ?: nbytes;
}