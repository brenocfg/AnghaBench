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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYSLOG ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ perf_cap__capable (int /*<<< orphan*/ ) ; 
 int perf_event_paranoid () ; 

__attribute__((used)) static bool symbol__read_kptr_restrict(void)
{
	bool value = false;
	FILE *fp = fopen("/proc/sys/kernel/kptr_restrict", "r");

	if (fp != NULL) {
		char line[8];

		if (fgets(line, sizeof(line), fp) != NULL)
			value = perf_cap__capable(CAP_SYSLOG) ?
					(atoi(line) >= 2) :
					(atoi(line) != 0);

		fclose(fp);
	}

	/* Per kernel/kallsyms.c:
	 * we also restrict when perf_event_paranoid > 1 w/o CAP_SYSLOG
	 */
	if (perf_event_paranoid() > 1 && !perf_cap__capable(CAP_SYSLOG))
		value = true;

	return value;
}