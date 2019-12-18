#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int size; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {scalar_t__ tid; TYPE_1__ header; struct TYPE_6__* comm; scalar_t__ pid; } ;
union perf_event {TYPE_2__ comm; } ;
typedef  int /*<<< orphan*/  u64 ;
struct machine {scalar_t__ pid; int id_hdr_size; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 size_t PERF_ALIGN (size_t,int) ; 
 int /*<<< orphan*/  PERF_RECORD_COMM ; 
 scalar_t__ machine__is_host (struct machine*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ perf_event__get_comm_ids (scalar_t__,TYPE_2__*,int,scalar_t__*,scalar_t__*) ; 
 int strlen (TYPE_2__*) ; 

__attribute__((used)) static int perf_event__prepare_comm(union perf_event *event, pid_t pid,
				    struct machine *machine,
				    pid_t *tgid, pid_t *ppid)
{
	size_t size;

	*ppid = -1;

	memset(&event->comm, 0, sizeof(event->comm));

	if (machine__is_host(machine)) {
		if (perf_event__get_comm_ids(pid, event->comm.comm,
					     sizeof(event->comm.comm),
					     tgid, ppid) != 0) {
			return -1;
		}
	} else {
		*tgid = machine->pid;
	}

	if (*tgid < 0)
		return -1;

	event->comm.pid = *tgid;
	event->comm.header.type = PERF_RECORD_COMM;

	size = strlen(event->comm.comm) + 1;
	size = PERF_ALIGN(size, sizeof(u64));
	memset(event->comm.comm + size, 0, machine->id_hdr_size);
	event->comm.header.size = (sizeof(event->comm) -
				(sizeof(event->comm.comm) - size) +
				machine->id_hdr_size);
	event->comm.tid = pid;

	return 0;
}