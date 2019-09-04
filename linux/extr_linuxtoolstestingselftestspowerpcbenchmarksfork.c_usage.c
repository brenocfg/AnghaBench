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
	fprintf(stderr, "Usage: fork <options> CPU\n\n");
	fprintf(stderr, "\t\t--fork\tUse fork() (default threads)\n");
	fprintf(stderr, "\t\t--vfork\tUse vfork() (default threads)\n");
	fprintf(stderr, "\t\t--exec\tAlso exec() (default no exec)\n");
	fprintf(stderr, "\t\t--timeout=X\tDuration in seconds to run (default 30)\n");
	fprintf(stderr, "\t\t--exec-target\tInternal option for exec workload\n");
}