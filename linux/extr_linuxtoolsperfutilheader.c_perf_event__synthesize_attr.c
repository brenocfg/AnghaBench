#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t size; int /*<<< orphan*/  type; } ;
struct perf_event_attr {int dummy; } ;
struct TYPE_4__ {TYPE_1__ header; int /*<<< orphan*/  id; struct perf_event_attr attr; } ;
union perf_event {TYPE_2__ attr; } ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
typedef  size_t u16 ;
struct perf_tool {int dummy; } ;
struct perf_event_header {int dummy; } ;
typedef  int (* perf_event__handler_t ) (struct perf_tool*,union perf_event*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;

/* Variables and functions */
 int E2BIG ; 
 int ENOMEM ; 
 size_t PERF_ALIGN (size_t,int) ; 
 int /*<<< orphan*/  PERF_RECORD_HEADER_ATTR ; 
 int /*<<< orphan*/  free (union perf_event*) ; 
 union perf_event* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int perf_event__synthesize_attr(struct perf_tool *tool,
				struct perf_event_attr *attr, u32 ids, u64 *id,
				perf_event__handler_t process)
{
	union perf_event *ev;
	size_t size;
	int err;

	size = sizeof(struct perf_event_attr);
	size = PERF_ALIGN(size, sizeof(u64));
	size += sizeof(struct perf_event_header);
	size += ids * sizeof(u64);

	ev = malloc(size);

	if (ev == NULL)
		return -ENOMEM;

	ev->attr.attr = *attr;
	memcpy(ev->attr.id, id, ids * sizeof(u64));

	ev->attr.header.type = PERF_RECORD_HEADER_ATTR;
	ev->attr.header.size = (u16)size;

	if (ev->attr.header.size == size)
		err = process(tool, ev, NULL, NULL);
	else
		err = -E2BIG;

	free(ev);

	return err;
}