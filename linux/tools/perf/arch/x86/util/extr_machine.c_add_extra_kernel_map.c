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
typedef  void* u64 ;
struct extra_kernel_map_info {size_t cnt; size_t max_cnt; TYPE_1__* maps; } ;
struct extra_kernel_map {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; void* pgoff; void* end; void* start; } ;

/* Variables and functions */
 int /*<<< orphan*/  KMAP_NAME_LEN ; 
 void* realloc (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_extra_kernel_map(struct extra_kernel_map_info *mi, u64 start,
				u64 end, u64 pgoff, const char *name)
{
	if (mi->cnt >= mi->max_cnt) {
		void *buf;
		size_t sz;

		mi->max_cnt = mi->max_cnt ? mi->max_cnt * 2 : 32;
		sz = sizeof(struct extra_kernel_map) * mi->max_cnt;
		buf = realloc(mi->maps, sz);
		if (!buf)
			return -1;
		mi->maps = buf;
	}

	mi->maps[mi->cnt].start = start;
	mi->maps[mi->cnt].end   = end;
	mi->maps[mi->cnt].pgoff = pgoff;
	strlcpy(mi->maps[mi->cnt].name, name, KMAP_NAME_LEN);

	mi->cnt += 1;

	return 0;
}