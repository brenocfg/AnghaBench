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
struct TYPE_2__ {int type; } ;
union perf_event {TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  PERF_RECORD_AUX 140 
#define  PERF_RECORD_BPF_EVENT 139 
#define  PERF_RECORD_COMM 138 
#define  PERF_RECORD_EXIT 137 
#define  PERF_RECORD_FORK 136 
#define  PERF_RECORD_ITRACE_START 135 
#define  PERF_RECORD_KSYMBOL 134 
#define  PERF_RECORD_LOST 133 
#define  PERF_RECORD_MMAP 132 
#define  PERF_RECORD_MMAP2 131 
#define  PERF_RECORD_NAMESPACES 130 
#define  PERF_RECORD_SWITCH 129 
#define  PERF_RECORD_SWITCH_CPU_WIDE 128 
 size_t fprintf (int /*<<< orphan*/ *,char*,...) ; 
 size_t perf_event__fprintf_aux (union perf_event*,int /*<<< orphan*/ *) ; 
 size_t perf_event__fprintf_bpf (union perf_event*,int /*<<< orphan*/ *) ; 
 size_t perf_event__fprintf_comm (union perf_event*,int /*<<< orphan*/ *) ; 
 size_t perf_event__fprintf_itrace_start (union perf_event*,int /*<<< orphan*/ *) ; 
 size_t perf_event__fprintf_ksymbol (union perf_event*,int /*<<< orphan*/ *) ; 
 size_t perf_event__fprintf_lost (union perf_event*,int /*<<< orphan*/ *) ; 
 size_t perf_event__fprintf_mmap (union perf_event*,int /*<<< orphan*/ *) ; 
 size_t perf_event__fprintf_mmap2 (union perf_event*,int /*<<< orphan*/ *) ; 
 size_t perf_event__fprintf_namespaces (union perf_event*,int /*<<< orphan*/ *) ; 
 size_t perf_event__fprintf_switch (union perf_event*,int /*<<< orphan*/ *) ; 
 size_t perf_event__fprintf_task (union perf_event*,int /*<<< orphan*/ *) ; 
 char* perf_event__name (int) ; 

size_t perf_event__fprintf(union perf_event *event, FILE *fp)
{
	size_t ret = fprintf(fp, "PERF_RECORD_%s",
			     perf_event__name(event->header.type));

	switch (event->header.type) {
	case PERF_RECORD_COMM:
		ret += perf_event__fprintf_comm(event, fp);
		break;
	case PERF_RECORD_FORK:
	case PERF_RECORD_EXIT:
		ret += perf_event__fprintf_task(event, fp);
		break;
	case PERF_RECORD_MMAP:
		ret += perf_event__fprintf_mmap(event, fp);
		break;
	case PERF_RECORD_NAMESPACES:
		ret += perf_event__fprintf_namespaces(event, fp);
		break;
	case PERF_RECORD_MMAP2:
		ret += perf_event__fprintf_mmap2(event, fp);
		break;
	case PERF_RECORD_AUX:
		ret += perf_event__fprintf_aux(event, fp);
		break;
	case PERF_RECORD_ITRACE_START:
		ret += perf_event__fprintf_itrace_start(event, fp);
		break;
	case PERF_RECORD_SWITCH:
	case PERF_RECORD_SWITCH_CPU_WIDE:
		ret += perf_event__fprintf_switch(event, fp);
		break;
	case PERF_RECORD_LOST:
		ret += perf_event__fprintf_lost(event, fp);
		break;
	case PERF_RECORD_KSYMBOL:
		ret += perf_event__fprintf_ksymbol(event, fp);
		break;
	case PERF_RECORD_BPF_EVENT:
		ret += perf_event__fprintf_bpf(event, fp);
		break;
	default:
		ret += fprintf(fp, "\n");
	}

	return ret;
}