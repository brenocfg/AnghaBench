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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int extract_sweep_id (unsigned int) ; 
 int extract_tid (unsigned int) ; 
 int extract_word_offset (unsigned int) ; 
 int /*<<< orphan*/ ** fp ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static inline void log_anamoly(unsigned int tid, unsigned int *addr,
			       unsigned int expected, unsigned int observed)
{
	FILE *f = fp[tid];

	fprintf(f, "Thread %02d: Addr 0x%lx: Expected 0x%x, Observed 0x%x\n",
	        tid, (unsigned long)addr, expected, observed);
	fprintf(f, "Thread %02d: Expected Thread id   = %02d\n", tid, extract_tid(expected));
	fprintf(f, "Thread %02d: Observed Thread id   = %02d\n", tid, extract_tid(observed));
	fprintf(f, "Thread %02d: Expected Word offset = %03d\n", tid, extract_word_offset(expected));
	fprintf(f, "Thread %02d: Observed Word offset = %03d\n", tid, extract_word_offset(observed));
	fprintf(f, "Thread %02d: Expected sweep-id    = 0x%x\n", tid, extract_sweep_id(expected));
	fprintf(f, "Thread %02d: Observed sweep-id    = 0x%x\n", tid, extract_sweep_id(observed));
	fprintf(f, "----------------------------------------------------------\n");
}