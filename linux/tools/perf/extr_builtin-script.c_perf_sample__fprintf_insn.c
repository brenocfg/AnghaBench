#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct thread {int dummy; } ;
struct perf_sample {scalar_t__ insn_len; scalar_t__* insn; } ;
struct perf_event_attr {int dummy; } ;
struct machine {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BRSTACKINSN ; 
 int /*<<< orphan*/  INSN ; 
 int /*<<< orphan*/  INSNLEN ; 
 scalar_t__ PRINT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_fetch_insn (struct perf_sample*,struct thread*,struct machine*) ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ native_arch ; 
 scalar_t__ perf_sample__fprintf_brstackinsn (struct perf_sample*,struct thread*,struct perf_event_attr*,struct machine*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int perf_sample__fprintf_insn(struct perf_sample *sample,
				     struct perf_event_attr *attr,
				     struct thread *thread,
				     struct machine *machine, FILE *fp)
{
	int printed = 0;

	if (sample->insn_len == 0 && native_arch)
		arch_fetch_insn(sample, thread, machine);

	if (PRINT_FIELD(INSNLEN))
		printed += fprintf(fp, " ilen: %d", sample->insn_len);
	if (PRINT_FIELD(INSN) && sample->insn_len) {
		int i;

		printed += fprintf(fp, " insn:");
		for (i = 0; i < sample->insn_len; i++)
			printed += fprintf(fp, " %02x", (unsigned char)sample->insn[i]);
	}
	if (PRINT_FIELD(BRSTACKINSN))
		printed += perf_sample__fprintf_brstackinsn(sample, thread, attr, machine, fp);

	return printed;
}