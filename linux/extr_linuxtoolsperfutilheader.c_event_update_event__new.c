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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ size; int /*<<< orphan*/  type; } ;
struct event_update_event {void* id; void* type; TYPE_1__ header; } ;

/* Variables and functions */
 size_t PERF_ALIGN (size_t,int) ; 
 int /*<<< orphan*/  PERF_RECORD_EVENT_UPDATE ; 
 struct event_update_event* zalloc (size_t) ; 

__attribute__((used)) static struct event_update_event *
event_update_event__new(size_t size, u64 type, u64 id)
{
	struct event_update_event *ev;

	size += sizeof(*ev);
	size  = PERF_ALIGN(size, sizeof(u64));

	ev = zalloc(size);
	if (ev) {
		ev->header.type = PERF_RECORD_EVENT_UPDATE;
		ev->header.size = (u16)size;
		ev->type = type;
		ev->id = id;
	}
	return ev;
}