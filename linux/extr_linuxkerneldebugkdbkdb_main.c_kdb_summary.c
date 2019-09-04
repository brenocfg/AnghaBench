#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time64_t ;
struct tm {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;
struct sysinfo {int uptime; int* loads; int totalram; int freeram; int bufferram; } ;
struct TYPE_4__ {int /*<<< orphan*/  domainname; int /*<<< orphan*/  nodename; int /*<<< orphan*/  machine; int /*<<< orphan*/  version; int /*<<< orphan*/  release; int /*<<< orphan*/  sysname; } ;
struct TYPE_6__ {TYPE_1__ name; } ;
struct TYPE_5__ {int /*<<< orphan*/  tz_minuteswest; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCVERSION ; 
 int FIXED_1 ; 
 int FSHIFT ; 
 int KDB_ARGCOUNT ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  __ktime_get_real_seconds () ; 
 int /*<<< orphan*/  __stringify (int /*<<< orphan*/ ) ; 
 TYPE_3__ init_uts_ns ; 
 int /*<<< orphan*/  kdb_printf (char*,...) ; 
 int /*<<< orphan*/  kdb_sysinfo (struct sysinfo*) ; 
 TYPE_2__ sys_tz ; 
 int /*<<< orphan*/  time64_to_tm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tm*) ; 

__attribute__((used)) static int kdb_summary(int argc, const char **argv)
{
	time64_t now;
	struct tm tm;
	struct sysinfo val;

	if (argc)
		return KDB_ARGCOUNT;

	kdb_printf("sysname    %s\n", init_uts_ns.name.sysname);
	kdb_printf("release    %s\n", init_uts_ns.name.release);
	kdb_printf("version    %s\n", init_uts_ns.name.version);
	kdb_printf("machine    %s\n", init_uts_ns.name.machine);
	kdb_printf("nodename   %s\n", init_uts_ns.name.nodename);
	kdb_printf("domainname %s\n", init_uts_ns.name.domainname);
	kdb_printf("ccversion  %s\n", __stringify(CCVERSION));

	now = __ktime_get_real_seconds();
	time64_to_tm(now, 0, &tm);
	kdb_printf("date       %04ld-%02d-%02d %02d:%02d:%02d "
		   "tz_minuteswest %d\n",
		1900+tm.tm_year, tm.tm_mon+1, tm.tm_mday,
		tm.tm_hour, tm.tm_min, tm.tm_sec,
		sys_tz.tz_minuteswest);

	kdb_sysinfo(&val);
	kdb_printf("uptime     ");
	if (val.uptime > (24*60*60)) {
		int days = val.uptime / (24*60*60);
		val.uptime %= (24*60*60);
		kdb_printf("%d day%s ", days, days == 1 ? "" : "s");
	}
	kdb_printf("%02ld:%02ld\n", val.uptime/(60*60), (val.uptime/60)%60);

	/* lifted from fs/proc/proc_misc.c::loadavg_read_proc() */

#define LOAD_INT(x) ((x) >> FSHIFT)
#define LOAD_FRAC(x) LOAD_INT(((x) & (FIXED_1-1)) * 100)
	kdb_printf("load avg   %ld.%02ld %ld.%02ld %ld.%02ld\n",
		LOAD_INT(val.loads[0]), LOAD_FRAC(val.loads[0]),
		LOAD_INT(val.loads[1]), LOAD_FRAC(val.loads[1]),
		LOAD_INT(val.loads[2]), LOAD_FRAC(val.loads[2]));
#undef LOAD_INT
#undef LOAD_FRAC
	/* Display in kilobytes */
#define K(x) ((x) << (PAGE_SHIFT - 10))
	kdb_printf("\nMemTotal:       %8lu kB\nMemFree:        %8lu kB\n"
		   "Buffers:        %8lu kB\n",
		   K(val.totalram), K(val.freeram), K(val.bufferram));
	return 0;
}