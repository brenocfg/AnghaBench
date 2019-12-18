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
struct TYPE_4__ {char* comm; int pid; int tid; } ;
struct TYPE_3__ {int misc; } ;
union perf_event {TYPE_2__ comm; TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int PERF_RECORD_MISC_COMM_EXEC ; 
 size_t fprintf (int /*<<< orphan*/ *,char*,char const*,char*,int,int) ; 

size_t perf_event__fprintf_comm(union perf_event *event, FILE *fp)
{
	const char *s;

	if (event->header.misc & PERF_RECORD_MISC_COMM_EXEC)
		s = " exec";
	else
		s = "";

	return fprintf(fp, "%s: %s:%d/%d\n", s, event->comm.comm, event->comm.pid, event->comm.tid);
}