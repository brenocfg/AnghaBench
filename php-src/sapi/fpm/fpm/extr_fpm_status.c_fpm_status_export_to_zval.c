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
typedef  int /*<<< orphan*/  zval ;
typedef  scalar_t__ time_t ;
struct timeval {unsigned long tv_sec; scalar_t__ tv_usec; } ;
struct fpm_scoreboard_s {char* pool; int nprocs; scalar_t__ slow_rq; scalar_t__ max_children_reached; scalar_t__ active_max; scalar_t__ active; scalar_t__ idle; scalar_t__ lq_len; scalar_t__ lq_max; scalar_t__ lq; scalar_t__ requests; scalar_t__ start_epoch; int /*<<< orphan*/  pm; } ;
struct TYPE_4__ {int tv_sec; int tv_usec; } ;
struct TYPE_3__ {int tms_utime; int tms_stime; int tms_cutime; int tms_cstime; } ;
struct fpm_scoreboard_proc_s {int used; scalar_t__ request_stage; char* request_method; char* request_uri; char* query_string; char* auth_user; char* script_filename; scalar_t__ memory; scalar_t__ content_length; int /*<<< orphan*/  accepted; struct timeval duration; scalar_t__ requests; scalar_t__ start_epoch; scalar_t__ pid; TYPE_2__ cpu_duration; TYPE_1__ last_request_cpu; } ;

/* Variables and functions */
 scalar_t__ FPM_REQUEST_ACCEPTING ; 
 char* PM2STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZLOG_NOTICE ; 
 int /*<<< orphan*/  add_assoc_double (int /*<<< orphan*/ *,char*,double) ; 
 int /*<<< orphan*/  add_assoc_long (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  add_assoc_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  add_assoc_zval (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_next_index_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fpm_clock_get (struct timeval*) ; 
 char* fpm_request_get_stage_name (scalar_t__) ; 
 struct fpm_scoreboard_s* fpm_scoreboard_acquire (int /*<<< orphan*/ *,int) ; 
 int fpm_scoreboard_get_tick () ; 
 struct fpm_scoreboard_proc_s* fpm_scoreboard_proc_acquire (struct fpm_scoreboard_s*,int,int) ; 
 int /*<<< orphan*/  fpm_scoreboard_proc_release (struct fpm_scoreboard_proc_s*) ; 
 int /*<<< orphan*/  fpm_scoreboard_release (struct fpm_scoreboard_s*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timersub (struct timeval*,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,char*) ; 

int fpm_status_export_to_zval(zval *status)
{
	struct fpm_scoreboard_s scoreboard, *scoreboard_p;
	zval fpm_proc_stats, fpm_proc_stat;
	time_t now_epoch;
	struct timeval duration, now;
	double cpu;
	int i;


	scoreboard_p = fpm_scoreboard_acquire(NULL, 1);
	if (!scoreboard_p) {
		zlog(ZLOG_NOTICE, "[pool %s] status: scoreboard already in use.", scoreboard_p->pool);
		return -1;
	}

	/* copy the scoreboard not to bother other processes */
	scoreboard = *scoreboard_p;
	struct fpm_scoreboard_proc_s procs[scoreboard.nprocs];

	struct fpm_scoreboard_proc_s *proc_p;
	for(i=0; i<scoreboard.nprocs; i++) {
		proc_p = fpm_scoreboard_proc_acquire(scoreboard_p, i, 1);
		if (!proc_p){
			procs[i].used=-1;
			continue;
		}
		procs[i] = *proc_p;
		fpm_scoreboard_proc_release(proc_p);
	}
	fpm_scoreboard_release(scoreboard_p);

	now_epoch = time(NULL);
	fpm_clock_get(&now);

	array_init(status);
	add_assoc_string(status, "pool", scoreboard.pool);
	add_assoc_string(status, "process-manager", PM2STR(scoreboard.pm));
	add_assoc_long(status, "start-time", scoreboard.start_epoch);
	add_assoc_long(status, "start-since", now_epoch - scoreboard.start_epoch);
	add_assoc_long(status, "accepted-conn", scoreboard.requests);
#ifdef HAVE_FPM_LQ
	add_assoc_long(status, "listen-queue", scoreboard.lq);
	add_assoc_long(status, "max-listen-queue", scoreboard.lq_max);
	add_assoc_long(status, "listen-queue-len", scoreboard.lq_len);
#endif
	add_assoc_long(status, "idle-processes", scoreboard.idle);
	add_assoc_long(status, "active-processes", scoreboard.active);
	add_assoc_long(status, "total-processes", scoreboard.idle + scoreboard.active);
	add_assoc_long(status, "max-active-processes", scoreboard.active_max);
	add_assoc_long(status, "max-children-reached", scoreboard.max_children_reached);
	add_assoc_long(status, "slow-requests", scoreboard.slow_rq);

	array_init(&fpm_proc_stats);
	for(i=0; i<scoreboard.nprocs; i++) {
		if (!procs[i].used) {
			continue;
		}
		proc_p = &procs[i];
#ifdef HAVE_FPM_LQ
		/* prevent NaN */
		if (procs[i].cpu_duration.tv_sec == 0 && procs[i].cpu_duration.tv_usec == 0) {
			cpu = 0.;
		} else {
			cpu = (procs[i].last_request_cpu.tms_utime + procs[i].last_request_cpu.tms_stime + procs[i].last_request_cpu.tms_cutime + procs[i].last_request_cpu.tms_cstime) / fpm_scoreboard_get_tick() / (procs[i].cpu_duration.tv_sec + procs[i].cpu_duration.tv_usec / 1000000.) * 100.;
		}
#endif

		array_init(&fpm_proc_stat);
		add_assoc_long(&fpm_proc_stat, "pid", procs[i].pid);
		add_assoc_string(&fpm_proc_stat, "state", fpm_request_get_stage_name(procs[i].request_stage));
		add_assoc_long(&fpm_proc_stat, "start-time", procs[i].start_epoch);
		add_assoc_long(&fpm_proc_stat, "start-since", now_epoch - procs[i].start_epoch);
		add_assoc_long(&fpm_proc_stat, "requests", procs[i].requests);
		if (procs[i].request_stage == FPM_REQUEST_ACCEPTING) {
			duration = procs[i].duration;
		} else {
			timersub(&now, &procs[i].accepted, &duration);
		}
		add_assoc_long(&fpm_proc_stat, "request-duration", duration.tv_sec * 1000000UL + duration.tv_usec);
		add_assoc_string(&fpm_proc_stat, "request-method", procs[i].request_method[0] != '\0' ? procs[i].request_method : "-");
		add_assoc_string(&fpm_proc_stat, "request-uri", procs[i].request_uri);
		add_assoc_string(&fpm_proc_stat, "query-string", procs[i].query_string);
		add_assoc_long(&fpm_proc_stat, "request-length", procs[i].content_length);
		add_assoc_string(&fpm_proc_stat, "user", procs[i].auth_user[0] != '\0' ? procs[i].auth_user : "-");
		add_assoc_string(&fpm_proc_stat, "script", procs[i].script_filename[0] != '\0' ? procs[i].script_filename : "-");
#ifdef HAVE_FPM_LQ
		add_assoc_double(&fpm_proc_stat, "last-request-cpu", procs[i].request_stage == FPM_REQUEST_ACCEPTING ? cpu : 0.);
#endif
		add_assoc_long(&fpm_proc_stat, "last-request-memory", procs[i].request_stage == FPM_REQUEST_ACCEPTING ? procs[i].memory : 0);
		add_next_index_zval(&fpm_proc_stats, &fpm_proc_stat);
	}
	add_assoc_zval(status, "procs", &fpm_proc_stats);
	return 0;
}