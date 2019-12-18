#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int size; void* type; } ;
struct TYPE_7__ {int /*<<< orphan*/  filename; int /*<<< orphan*/  pid; scalar_t__ len; scalar_t__ start; TYPE_2__ header; } ;
struct TYPE_5__ {int /*<<< orphan*/  misc; void* type; } ;
union perf_event {TYPE_3__ mmap; TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  u64 ;
struct perf_tool {int dummy; } ;
struct maps {int dummy; } ;
struct map {TYPE_4__* dso; scalar_t__ start; scalar_t__ end; } ;
struct machine {int id_hdr_size; int /*<<< orphan*/  pid; } ;
typedef  int /*<<< orphan*/  perf_event__handler_t ;
struct TYPE_8__ {scalar_t__ long_name_len; int /*<<< orphan*/  long_name; } ;

/* Variables and functions */
 size_t PERF_ALIGN (scalar_t__,int) ; 
 int /*<<< orphan*/  PERF_RECORD_MISC_GUEST_KERNEL ; 
 int /*<<< orphan*/  PERF_RECORD_MISC_KERNEL ; 
 void* PERF_RECORD_MMAP ; 
 int /*<<< orphan*/  __map__is_kmodule (struct map*) ; 
 int /*<<< orphan*/  free (union perf_event*) ; 
 scalar_t__ machine__is_host (struct machine*) ; 
 struct maps* machine__kernel_maps (struct machine*) ; 
 struct map* map__next (struct map*) ; 
 struct map* maps__first (struct maps*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ perf_tool__process_synth_event (struct perf_tool*,union perf_event*,struct machine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 union perf_event* zalloc (int) ; 

int perf_event__synthesize_modules(struct perf_tool *tool, perf_event__handler_t process,
				   struct machine *machine)
{
	int rc = 0;
	struct map *pos;
	struct maps *maps = machine__kernel_maps(machine);
	union perf_event *event = zalloc((sizeof(event->mmap) +
					  machine->id_hdr_size));
	if (event == NULL) {
		pr_debug("Not enough memory synthesizing mmap event "
			 "for kernel modules\n");
		return -1;
	}

	event->header.type = PERF_RECORD_MMAP;

	/*
	 * kernel uses 0 for user space maps, see kernel/perf_event.c
	 * __perf_event_mmap
	 */
	if (machine__is_host(machine))
		event->header.misc = PERF_RECORD_MISC_KERNEL;
	else
		event->header.misc = PERF_RECORD_MISC_GUEST_KERNEL;

	for (pos = maps__first(maps); pos; pos = map__next(pos)) {
		size_t size;

		if (!__map__is_kmodule(pos))
			continue;

		size = PERF_ALIGN(pos->dso->long_name_len + 1, sizeof(u64));
		event->mmap.header.type = PERF_RECORD_MMAP;
		event->mmap.header.size = (sizeof(event->mmap) -
				        (sizeof(event->mmap.filename) - size));
		memset(event->mmap.filename + size, 0, machine->id_hdr_size);
		event->mmap.header.size += machine->id_hdr_size;
		event->mmap.start = pos->start;
		event->mmap.len   = pos->end - pos->start;
		event->mmap.pid   = machine->pid;

		memcpy(event->mmap.filename, pos->dso->long_name,
		       pos->dso->long_name_len + 1);
		if (perf_tool__process_synth_event(tool, event, machine, process) != 0) {
			rc = -1;
			break;
		}
	}

	free(event);
	return rc;
}