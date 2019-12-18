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

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void usage(void)
{
	fprintf(stderr, "Usage: context_switch2 <options> CPU1 CPU2\n\n");
	fprintf(stderr, "\t\t--test=X\tpipe, futex or yield (default)\n");
	fprintf(stderr, "\t\t--process\tUse processes (default threads)\n");
	fprintf(stderr, "\t\t--timeout=X\tDuration in seconds to run (default 30)\n");
	fprintf(stderr, "\t\t--vdso\t\ttouch VDSO\n");
	fprintf(stderr, "\t\t--no-fp\t\tDon't touch FP\n");
#ifdef __powerpc__
	fprintf(stderr, "\t\t--no-altivec\tDon't touch altivec\n");
#endif
	fprintf(stderr, "\t\t--no-vector\tDon't touch vector\n");
}