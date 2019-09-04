#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t size; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int /*<<< orphan*/  filename; int /*<<< orphan*/  pid; int /*<<< orphan*/  pgoff; scalar_t__ len; scalar_t__ start; TYPE_2__ header; } ;
struct TYPE_4__ {int /*<<< orphan*/  misc; } ;
union perf_event {TYPE_3__ mmap; TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  u64 ;
struct perf_tool {int dummy; } ;
struct maps {int dummy; } ;
struct map_groups {struct maps maps; } ;
struct map {int /*<<< orphan*/  pgoff; scalar_t__ start; scalar_t__ end; } ;
struct machine {int id_hdr_size; int /*<<< orphan*/  pid; struct map_groups kmaps; } ;
struct kmap {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  perf_event__handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_MAX ; 
 int PERF_ALIGN (scalar_t__,int) ; 
 int /*<<< orphan*/  PERF_RECORD_MISC_GUEST_KERNEL ; 
 int /*<<< orphan*/  PERF_RECORD_MISC_KERNEL ; 
 int /*<<< orphan*/  PERF_RECORD_MMAP ; 
 int /*<<< orphan*/  __map__is_extra_kernel_map (struct map*) ; 
 int /*<<< orphan*/  free (union perf_event*) ; 
 scalar_t__ machine__is_host (struct machine*) ; 
 struct kmap* map__kmap (struct map*) ; 
 struct map* map__next (struct map*) ; 
 struct map* maps__first (struct maps*) ; 
 int /*<<< orphan*/  memset (union perf_event*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ perf_tool__process_synth_event (struct perf_tool*,union perf_event*,struct machine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 union perf_event* zalloc (int) ; 

int perf_event__synthesize_extra_kmaps(struct perf_tool *tool,
				       perf_event__handler_t process,
				       struct machine *machine)
{
	int rc = 0;
	struct map *pos;
	struct map_groups *kmaps = &machine->kmaps;
	struct maps *maps = &kmaps->maps;
	union perf_event *event = zalloc(sizeof(event->mmap) +
					 machine->id_hdr_size);

	if (!event) {
		pr_debug("Not enough memory synthesizing mmap event "
			 "for extra kernel maps\n");
		return -1;
	}

	for (pos = maps__first(maps); pos; pos = map__next(pos)) {
		struct kmap *kmap;
		size_t size;

		if (!__map__is_extra_kernel_map(pos))
			continue;

		kmap = map__kmap(pos);

		size = sizeof(event->mmap) - sizeof(event->mmap.filename) +
		       PERF_ALIGN(strlen(kmap->name) + 1, sizeof(u64)) +
		       machine->id_hdr_size;

		memset(event, 0, size);

		event->mmap.header.type = PERF_RECORD_MMAP;

		/*
		 * kernel uses 0 for user space maps, see kernel/perf_event.c
		 * __perf_event_mmap
		 */
		if (machine__is_host(machine))
			event->header.misc = PERF_RECORD_MISC_KERNEL;
		else
			event->header.misc = PERF_RECORD_MISC_GUEST_KERNEL;

		event->mmap.header.size = size;

		event->mmap.start = pos->start;
		event->mmap.len   = pos->end - pos->start;
		event->mmap.pgoff = pos->pgoff;
		event->mmap.pid   = machine->pid;

		strlcpy(event->mmap.filename, kmap->name, PATH_MAX);

		if (perf_tool__process_synth_event(tool, event, machine,
						   process) != 0) {
			rc = -1;
			break;
		}
	}

	free(event);
	return rc;
}