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
struct TYPE_2__ {int /*<<< orphan*/  filename; void* ino; void* min; void* maj; void* pgoff; void* len; void* start; void* tid; void* pid; } ;
union perf_event {TYPE_1__ mmap2; } ;
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_ALIGN (scalar_t__,int) ; 
 void* bswap_32 (void*) ; 
 void* bswap_64 (void*) ; 
 scalar_t__ strlen (void*) ; 
 int /*<<< orphan*/  swap_sample_id_all (union perf_event*,void*) ; 

__attribute__((used)) static void perf_event__mmap2_swap(union perf_event *event,
				  bool sample_id_all)
{
	event->mmap2.pid   = bswap_32(event->mmap2.pid);
	event->mmap2.tid   = bswap_32(event->mmap2.tid);
	event->mmap2.start = bswap_64(event->mmap2.start);
	event->mmap2.len   = bswap_64(event->mmap2.len);
	event->mmap2.pgoff = bswap_64(event->mmap2.pgoff);
	event->mmap2.maj   = bswap_32(event->mmap2.maj);
	event->mmap2.min   = bswap_32(event->mmap2.min);
	event->mmap2.ino   = bswap_64(event->mmap2.ino);

	if (sample_id_all) {
		void *data = &event->mmap2.filename;

		data += PERF_ALIGN(strlen(data) + 1, sizeof(u64));
		swap_sample_id_all(event, data);
	}
}