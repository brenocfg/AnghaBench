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
struct TYPE_3__ {int size; int /*<<< orphan*/  misc; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int /*<<< orphan*/  filename; TYPE_1__ header; int /*<<< orphan*/  pid; int /*<<< orphan*/  build_id; } ;
union perf_event {TYPE_2__ build_id; } ;
typedef  int /*<<< orphan*/  u16 ;
struct perf_tool {int dummy; } ;
struct machine {int /*<<< orphan*/  pid; } ;
struct dso {int long_name_len; int /*<<< orphan*/  long_name; int /*<<< orphan*/  build_id; int /*<<< orphan*/  hit; } ;
typedef  int (* perf_event__handler_t ) (struct perf_tool*,union perf_event*,int /*<<< orphan*/ *,struct machine*) ;
typedef  int /*<<< orphan*/  ev ;

/* Variables and functions */
 int /*<<< orphan*/  NAME_ALIGN ; 
 size_t PERF_ALIGN (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERF_RECORD_HEADER_BUILD_ID ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (union perf_event*,int /*<<< orphan*/ ,int) ; 

int perf_event__synthesize_build_id(struct perf_tool *tool,
				    struct dso *pos, u16 misc,
				    perf_event__handler_t process,
				    struct machine *machine)
{
	union perf_event ev;
	size_t len;
	int err = 0;

	if (!pos->hit)
		return err;

	memset(&ev, 0, sizeof(ev));

	len = pos->long_name_len + 1;
	len = PERF_ALIGN(len, NAME_ALIGN);
	memcpy(&ev.build_id.build_id, pos->build_id, sizeof(pos->build_id));
	ev.build_id.header.type = PERF_RECORD_HEADER_BUILD_ID;
	ev.build_id.header.misc = misc;
	ev.build_id.pid = machine->pid;
	ev.build_id.header.size = sizeof(ev.build_id) + len;
	memcpy(&ev.build_id.filename, pos->long_name, pos->long_name_len);

	err = process(tool, &ev, NULL, machine);

	return err;
}