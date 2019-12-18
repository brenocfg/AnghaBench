#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_uid; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  binding_str ;
struct TYPE_8__ {int nr_tz_sensor; int nr_cooling_dev; TYPE_3__* cdi; TYPE_2__* tzi; } ;
struct TYPE_7__ {char* type; int /*<<< orphan*/  instance; } ;
struct TYPE_6__ {int cdev_binding; char* type; char* instance; int nr_trip_pts; TYPE_1__* tp; } ;
struct TYPE_5__ {size_t type; int /*<<< orphan*/  temp; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TMON_LOG_FILE ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  logging ; 
 scalar_t__ lstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__ ptdata ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * tmon_log ; 
 char** trip_type_name ; 

__attribute__((used)) static void prepare_logging(void)
{
	int i;
	struct stat logstat;

	if (!logging)
		return;
	/* open local data log file */
	tmon_log = fopen(TMON_LOG_FILE, "w+");
	if (!tmon_log) {
		syslog(LOG_ERR, "failed to open log file %s\n", TMON_LOG_FILE);
		return;
	}

	if (lstat(TMON_LOG_FILE, &logstat) < 0) {
		syslog(LOG_ERR, "Unable to stat log file %s\n", TMON_LOG_FILE);
		fclose(tmon_log);
		tmon_log = NULL;
		return;
	}

	/* The log file must be a regular file owned by us */
	if (S_ISLNK(logstat.st_mode)) {
		syslog(LOG_ERR, "Log file is a symlink.  Will not log\n");
		fclose(tmon_log);
		tmon_log = NULL;
		return;
	}

	if (logstat.st_uid != getuid()) {
		syslog(LOG_ERR, "We don't own the log file.  Not logging\n");
		fclose(tmon_log);
		tmon_log = NULL;
		return;
	}


	fprintf(tmon_log, "#----------- THERMAL SYSTEM CONFIG -------------\n");
	for (i = 0; i < ptdata.nr_tz_sensor; i++) {
		char binding_str[33]; /* size of long + 1 */
		int j;

		memset(binding_str, 0, sizeof(binding_str));
		for (j = 0; j < 32; j++)
			binding_str[j] = (ptdata.tzi[i].cdev_binding & 1<<j) ?
				'1' : '0';

		fprintf(tmon_log, "#thermal zone %s%02d cdevs binding: %32s\n",
			ptdata.tzi[i].type,
			ptdata.tzi[i].instance,
			binding_str);
		for (j = 0; j <	ptdata.tzi[i].nr_trip_pts; j++) {
			fprintf(tmon_log, "#\tTP%02d type:%s, temp:%lu\n", j,
				trip_type_name[ptdata.tzi[i].tp[j].type],
				ptdata.tzi[i].tp[j].temp);
		}

	}

	for (i = 0; i <	ptdata.nr_cooling_dev; i++)
		fprintf(tmon_log, "#cooling devices%02d: %s\n",
			i, ptdata.cdi[i].type);

	fprintf(tmon_log, "#---------- THERMAL DATA LOG STARTED -----------\n");
	fprintf(tmon_log, "Samples TargetTemp ");
	for (i = 0; i < ptdata.nr_tz_sensor; i++) {
		fprintf(tmon_log, "%s%d    ", ptdata.tzi[i].type,
			ptdata.tzi[i].instance);
	}
	for (i = 0; i <	ptdata.nr_cooling_dev; i++)
		fprintf(tmon_log, "%s%d ", ptdata.cdi[i].type,
			ptdata.cdi[i].instance);

	fprintf(tmon_log, "\n");
}