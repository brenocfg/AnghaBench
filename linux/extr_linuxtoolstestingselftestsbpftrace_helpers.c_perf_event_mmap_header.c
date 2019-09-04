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
struct perf_event_mmap_page {int dummy; } ;

/* Variables and functions */
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int getpagesize () ; 
 void* mmap (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int page_cnt ; 
 int page_size ; 
 int /*<<< orphan*/  printf (char*) ; 

int perf_event_mmap_header(int fd, struct perf_event_mmap_page **header)
{
	void *base;
	int mmap_size;

	page_size = getpagesize();
	mmap_size = page_size * (page_cnt + 1);

	base = mmap(NULL, mmap_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (base == MAP_FAILED) {
		printf("mmap err\n");
		return -1;
	}

	*header = base;
	return 0;
}