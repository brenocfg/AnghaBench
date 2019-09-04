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
struct mem_cgroup {struct page_counter tcpmem; struct page_counter kmem; struct page_counter memsw; struct page_counter memory; } ;
struct kernfs_open_file {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int MEMFILE_ATTR (int /*<<< orphan*/ ) ; 
 int MEMFILE_TYPE (int /*<<< orphan*/ ) ; 
#define  RES_FAILCNT 133 
#define  RES_MAX_USAGE 132 
#define  _KMEM 131 
#define  _MEM 130 
#define  _MEMSWAP 129 
#define  _TCP 128 
 struct mem_cgroup* mem_cgroup_from_css (int /*<<< orphan*/ ) ; 
 TYPE_1__* of_cft (struct kernfs_open_file*) ; 
 int /*<<< orphan*/  of_css (struct kernfs_open_file*) ; 
 int /*<<< orphan*/  page_counter_reset_watermark (struct page_counter*) ; 

__attribute__((used)) static ssize_t mem_cgroup_reset(struct kernfs_open_file *of, char *buf,
				size_t nbytes, loff_t off)
{
	struct mem_cgroup *memcg = mem_cgroup_from_css(of_css(of));
	struct page_counter *counter;

	switch (MEMFILE_TYPE(of_cft(of)->private)) {
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

	switch (MEMFILE_ATTR(of_cft(of)->private)) {
	case RES_MAX_USAGE:
		page_counter_reset_watermark(counter);
		break;
	case RES_FAILCNT:
		counter->failcnt = 0;
		break;
	default:
		BUG();
	}

	return nbytes;
}