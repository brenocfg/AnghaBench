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
typedef  int /*<<< orphan*/  usec_t ;
typedef  scalar_t__ uint32_t ;
struct stat {int dummy; } ;
struct per_core_cpuidle_chart {unsigned long long active_time; unsigned long long last_active_time; size_t cpuidle_state_len; int /*<<< orphan*/ * st; TYPE_3__* cpuidle_state; int /*<<< orphan*/ * active_time_rd; } ;
struct TYPE_5__ {int /*<<< orphan*/ * ff; void* filename; } ;
struct cpu_chart {int /*<<< orphan*/ * st; int /*<<< orphan*/ * rd_guest_nice; int /*<<< orphan*/ * rd_guest; int /*<<< orphan*/ * rd_steal; int /*<<< orphan*/ * rd_softirq; int /*<<< orphan*/ * rd_irq; int /*<<< orphan*/ * rd_iowait; int /*<<< orphan*/ * rd_idle; int /*<<< orphan*/ * rd_system; int /*<<< orphan*/ * rd_nice; int /*<<< orphan*/ * rd_user; TYPE_2__ time_in_state_files; TYPE_1__* files; void* id; } ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  procfile ;
struct TYPE_6__ {char* name; unsigned long long value; int /*<<< orphan*/ * rd; } ;
struct TYPE_4__ {int fd; void* filename; } ;
typedef  int /*<<< orphan*/  RRDVAR ;
typedef  int /*<<< orphan*/  RRDSET ;
typedef  int /*<<< orphan*/  RRDDIM ;

/* Variables and functions */
 int CONFIG_BOOLEAN_AUTO ; 
 int CONFIG_BOOLEAN_NO ; 
 int CONFIG_BOOLEAN_YES ; 
 size_t CORE_THROTTLE_COUNT_INDEX ; 
 size_t CPU_FREQ_INDEX ; 
 int /*<<< orphan*/  FILENAME_MAX ; 
 size_t NETDATA_CHART_PRIO_CORE_THROTTLING ; 
 size_t NETDATA_CHART_PRIO_CPUFREQ_SCALING_CUR_FREQ ; 
 size_t NETDATA_CHART_PRIO_CPUIDLE ; 
 long NETDATA_CHART_PRIO_CPU_PER_CORE ; 
 size_t NETDATA_CHART_PRIO_PACKAGE_THROTTLING ; 
 long NETDATA_CHART_PRIO_SYSTEM_CPU ; 
 size_t NETDATA_CHART_PRIO_SYSTEM_CTXT ; 
 size_t NETDATA_CHART_PRIO_SYSTEM_FORKS ; 
 size_t NETDATA_CHART_PRIO_SYSTEM_INTR ; 
 size_t NETDATA_CHART_PRIO_SYSTEM_PROCESSES ; 
 size_t PACKAGE_THROTTLE_COUNT_INDEX ; 
 int /*<<< orphan*/  PLUGIN_PROC_MODULE_STAT_NAME ; 
 int /*<<< orphan*/  PLUGIN_PROC_NAME ; 
 int /*<<< orphan*/  PROCFILE_FLAG_DEFAULT ; 
 int /*<<< orphan*/  RRDSET_FLAG_DETAIL ; 
 int /*<<< orphan*/  RRDSET_TYPE_LINE ; 
 int /*<<< orphan*/  RRDSET_TYPE_STACKED ; 
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_INCREMENTAL ; 
 int /*<<< orphan*/  RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL ; 
 int /*<<< orphan*/  RRD_ID_LENGTH_MAX ; 
 int /*<<< orphan*/  chart_per_core_files (struct cpu_chart*,size_t,size_t,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 char* config_get (char*,char*,char*) ; 
 int config_get_boolean (char*,char*,int) ; 
 int config_get_boolean_ondemand (char*,char*,int) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  info (char*,char*) ; 
 int keep_cpuidle_fds_open ; 
 int keep_per_core_fds_open ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  localhost ; 
 int /*<<< orphan*/  memset (struct cpu_chart*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdata_configured_host_prefix ; 
 int processors ; 
 size_t procfile_lines (int /*<<< orphan*/ *) ; 
 char* procfile_lineword (int /*<<< orphan*/ *,size_t,int) ; 
 size_t procfile_linewords (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * procfile_open (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * procfile_readall (int /*<<< orphan*/ *) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int read_cpuidle_states (char*,char*,struct per_core_cpuidle_chart*,size_t) ; 
 int read_per_core_files (struct cpu_chart*,size_t,size_t) ; 
 int read_per_core_time_in_state_files (struct cpu_chart*,size_t,size_t) ; 
 int /*<<< orphan*/  read_schedstat (char*,struct per_core_cpuidle_chart**,size_t*) ; 
 struct cpu_chart* reallocz (struct cpu_chart*,int) ; 
 void* rrddim_add (int /*<<< orphan*/ *,char*,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_hide (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long long) ; 
 void* rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_flag_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rrdvar_custom_host_variable_create (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rrdvar_custom_host_variable_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ simple_hash (char*) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 size_t str2ul (char*) ; 
 unsigned long long str2ull (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 void* strdupz (char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_cpu_thread ; 

int do_proc_stat(int update_every, usec_t dt) {
    (void)dt;

    static struct cpu_chart *all_cpu_charts = NULL;
    static size_t all_cpu_charts_size = 0;
    static procfile *ff = NULL;
    static int do_cpu = -1, do_cpu_cores = -1, do_interrupts = -1, do_context = -1, do_forks = -1, do_processes = -1,
           do_core_throttle_count = -1, do_package_throttle_count = -1, do_cpu_freq = -1, do_cpuidle = -1;
    static uint32_t hash_intr, hash_ctxt, hash_processes, hash_procs_running, hash_procs_blocked;
    static char *core_throttle_count_filename = NULL, *package_throttle_count_filename = NULL, *scaling_cur_freq_filename = NULL,
           *time_in_state_filename = NULL, *schedstat_filename = NULL, *cpuidle_name_filename = NULL, *cpuidle_time_filename = NULL;
    static RRDVAR *cpus_var = NULL;
    static int accurate_freq_avail = 0, accurate_freq_is_used = 0;
    size_t cores_found = (size_t)processors;

    if(unlikely(do_cpu == -1)) {
        do_cpu                    = config_get_boolean("plugin:proc:/proc/stat", "cpu utilization", CONFIG_BOOLEAN_YES);
        do_cpu_cores              = config_get_boolean("plugin:proc:/proc/stat", "per cpu core utilization", CONFIG_BOOLEAN_YES);
        do_interrupts             = config_get_boolean("plugin:proc:/proc/stat", "cpu interrupts", CONFIG_BOOLEAN_YES);
        do_context                = config_get_boolean("plugin:proc:/proc/stat", "context switches", CONFIG_BOOLEAN_YES);
        do_forks                  = config_get_boolean("plugin:proc:/proc/stat", "processes started", CONFIG_BOOLEAN_YES);
        do_processes              = config_get_boolean("plugin:proc:/proc/stat", "processes running", CONFIG_BOOLEAN_YES);

        // give sane defaults based on the number of processors
        if(unlikely(processors > 50)) {
            // the system has too many processors
            keep_per_core_fds_open = CONFIG_BOOLEAN_NO;
            do_core_throttle_count = CONFIG_BOOLEAN_NO;
            do_package_throttle_count = CONFIG_BOOLEAN_NO;
            do_cpu_freq = CONFIG_BOOLEAN_NO;
            do_cpuidle = CONFIG_BOOLEAN_NO;
        }
        else {
            // the system has a reasonable number of processors
            keep_per_core_fds_open = CONFIG_BOOLEAN_YES;
            do_core_throttle_count = CONFIG_BOOLEAN_AUTO;
            do_package_throttle_count = CONFIG_BOOLEAN_NO;
            do_cpu_freq = CONFIG_BOOLEAN_YES;
            do_cpuidle = CONFIG_BOOLEAN_YES;
        }
        if(unlikely(processors > 24)) {
            // the system has too many processors
            keep_cpuidle_fds_open = CONFIG_BOOLEAN_NO;
        }
        else {
            // the system has a reasonable number of processors
            keep_cpuidle_fds_open = CONFIG_BOOLEAN_YES;
        }

        keep_per_core_fds_open    = config_get_boolean("plugin:proc:/proc/stat", "keep per core files open", keep_per_core_fds_open);
        keep_cpuidle_fds_open     = config_get_boolean("plugin:proc:/proc/stat", "keep cpuidle files open", keep_cpuidle_fds_open);
        do_core_throttle_count    = config_get_boolean_ondemand("plugin:proc:/proc/stat", "core_throttle_count", do_core_throttle_count);
        do_package_throttle_count = config_get_boolean_ondemand("plugin:proc:/proc/stat", "package_throttle_count", do_package_throttle_count);
        do_cpu_freq               = config_get_boolean_ondemand("plugin:proc:/proc/stat", "cpu frequency", do_cpu_freq);
        do_cpuidle                = config_get_boolean_ondemand("plugin:proc:/proc/stat", "cpu idle states", do_cpuidle);

        hash_intr = simple_hash("intr");
        hash_ctxt = simple_hash("ctxt");
        hash_processes = simple_hash("processes");
        hash_procs_running = simple_hash("procs_running");
        hash_procs_blocked = simple_hash("procs_blocked");

        char filename[FILENAME_MAX + 1];
        snprintfz(filename, FILENAME_MAX, "%s%s", netdata_configured_host_prefix, "/sys/devices/system/cpu/%s/thermal_throttle/core_throttle_count");
        core_throttle_count_filename = config_get("plugin:proc:/proc/stat", "core_throttle_count filename to monitor", filename);

        snprintfz(filename, FILENAME_MAX, "%s%s", netdata_configured_host_prefix, "/sys/devices/system/cpu/%s/thermal_throttle/package_throttle_count");
        package_throttle_count_filename = config_get("plugin:proc:/proc/stat", "package_throttle_count filename to monitor", filename);

        snprintfz(filename, FILENAME_MAX, "%s%s", netdata_configured_host_prefix, "/sys/devices/system/cpu/%s/cpufreq/scaling_cur_freq");
        scaling_cur_freq_filename = config_get("plugin:proc:/proc/stat", "scaling_cur_freq filename to monitor", filename);

        snprintfz(filename, FILENAME_MAX, "%s%s", netdata_configured_host_prefix, "/sys/devices/system/cpu/%s/cpufreq/stats/time_in_state");
        time_in_state_filename = config_get("plugin:proc:/proc/stat", "time_in_state filename to monitor", filename);

        snprintfz(filename, FILENAME_MAX, "%s%s", netdata_configured_host_prefix, "/proc/schedstat");
        schedstat_filename = config_get("plugin:proc:/proc/stat", "schedstat filename to monitor", filename);

        if(do_cpuidle != CONFIG_BOOLEAN_NO) {
            struct stat stbuf;

            if (stat(schedstat_filename, &stbuf))
                do_cpuidle = CONFIG_BOOLEAN_NO;
        }

        snprintfz(filename, FILENAME_MAX, "%s%s", netdata_configured_host_prefix, "/sys/devices/system/cpu/cpu%zu/cpuidle/state%zu/name");
        cpuidle_name_filename = config_get("plugin:proc:/proc/stat", "cpuidle name filename to monitor", filename);

        snprintfz(filename, FILENAME_MAX, "%s%s", netdata_configured_host_prefix, "/sys/devices/system/cpu/cpu%zu/cpuidle/state%zu/time");
        cpuidle_time_filename = config_get("plugin:proc:/proc/stat", "cpuidle time filename to monitor", filename);
    }

    if(unlikely(!ff)) {
        char filename[FILENAME_MAX + 1];
        snprintfz(filename, FILENAME_MAX, "%s%s", netdata_configured_host_prefix, "/proc/stat");
        ff = procfile_open(config_get("plugin:proc:/proc/stat", "filename to monitor", filename), " \t:", PROCFILE_FLAG_DEFAULT);
        if(unlikely(!ff)) return 1;
    }

    ff = procfile_readall(ff);
    if(unlikely(!ff)) return 0; // we return 0, so that we will retry to open it next time

    size_t lines = procfile_lines(ff), l;
    size_t words;

    unsigned long long processes = 0, running = 0 , blocked = 0;

    for(l = 0; l < lines ;l++) {
        char *row_key = procfile_lineword(ff, l, 0);
        uint32_t hash = simple_hash(row_key);

        // faster strncmp(row_key, "cpu", 3) == 0
        if(likely(row_key[0] == 'c' && row_key[1] == 'p' && row_key[2] == 'u')) {
            words = procfile_linewords(ff, l);
            if(unlikely(words < 9)) {
                error("Cannot read /proc/stat cpu line. Expected 9 params, read %zu.", words);
                continue;
            }

            size_t core    = (row_key[3] == '\0') ? 0 : str2ul(&row_key[3]) + 1;
            if(likely(core > 0)) cores_found = core;

            if(likely((core == 0 && do_cpu) || (core > 0 && do_cpu_cores))) {
                char *id;
                unsigned long long user = 0, nice = 0, system = 0, idle = 0, iowait = 0, irq = 0, softirq = 0, steal = 0, guest = 0, guest_nice = 0;

                id          = row_key;
                user        = str2ull(procfile_lineword(ff, l, 1));
                nice        = str2ull(procfile_lineword(ff, l, 2));
                system      = str2ull(procfile_lineword(ff, l, 3));
                idle        = str2ull(procfile_lineword(ff, l, 4));
                iowait      = str2ull(procfile_lineword(ff, l, 5));
                irq         = str2ull(procfile_lineword(ff, l, 6));
                softirq     = str2ull(procfile_lineword(ff, l, 7));
                steal       = str2ull(procfile_lineword(ff, l, 8));

                guest       = str2ull(procfile_lineword(ff, l, 9));
                user -= guest;

                guest_nice  = str2ull(procfile_lineword(ff, l, 10));
                nice -= guest_nice;

                char *title, *type, *context, *family;
                long priority;

                if(unlikely(core >= all_cpu_charts_size)) {
                    size_t old_cpu_charts_size = all_cpu_charts_size;
                    all_cpu_charts_size = core + 1;
                    all_cpu_charts = reallocz(all_cpu_charts, sizeof(struct cpu_chart) * all_cpu_charts_size);
                    memset(&all_cpu_charts[old_cpu_charts_size], 0, sizeof(struct cpu_chart) * (all_cpu_charts_size - old_cpu_charts_size));
                }
                struct cpu_chart *cpu_chart = &all_cpu_charts[core];

                if(unlikely(!cpu_chart->st)) {
                    cpu_chart->id = strdupz(id);

                    if(unlikely(core == 0)) {
                        title = "Total CPU utilization";
                        type = "system";
                        context = "system.cpu";
                        family = id;
                        priority = NETDATA_CHART_PRIO_SYSTEM_CPU;
                    }
                    else {
                        title = "Core utilization";
                        type = "cpu";
                        context = "cpu.cpu";
                        family = "utilization";
                        priority = NETDATA_CHART_PRIO_CPU_PER_CORE;

                        char filename[FILENAME_MAX + 1];
                        struct stat stbuf;

                        if(do_core_throttle_count != CONFIG_BOOLEAN_NO) {
                            snprintfz(filename, FILENAME_MAX, core_throttle_count_filename, id);
                            if (stat(filename, &stbuf) == 0) {
                                cpu_chart->files[CORE_THROTTLE_COUNT_INDEX].filename = strdupz(filename);
                                cpu_chart->files[CORE_THROTTLE_COUNT_INDEX].fd = -1;
                                do_core_throttle_count = CONFIG_BOOLEAN_YES;
                            }
                        }

                        if(do_package_throttle_count != CONFIG_BOOLEAN_NO) {
                            snprintfz(filename, FILENAME_MAX, package_throttle_count_filename, id);
                            if (stat(filename, &stbuf) == 0) {
                                cpu_chart->files[PACKAGE_THROTTLE_COUNT_INDEX].filename = strdupz(filename);
                                cpu_chart->files[PACKAGE_THROTTLE_COUNT_INDEX].fd = -1;
                                do_package_throttle_count = CONFIG_BOOLEAN_YES;
                            }
                        }

                        if(do_cpu_freq != CONFIG_BOOLEAN_NO) {

                            snprintfz(filename, FILENAME_MAX, scaling_cur_freq_filename, id);

                            if (stat(filename, &stbuf) == 0) {
                                cpu_chart->files[CPU_FREQ_INDEX].filename = strdupz(filename);
                                cpu_chart->files[CPU_FREQ_INDEX].fd = -1;
                                do_cpu_freq = CONFIG_BOOLEAN_YES;
                            }

                            snprintfz(filename, FILENAME_MAX, time_in_state_filename, id);

                            if (stat(filename, &stbuf) == 0) {
                                cpu_chart->time_in_state_files.filename = strdupz(filename);
                                cpu_chart->time_in_state_files.ff = NULL;
                                do_cpu_freq = CONFIG_BOOLEAN_YES;
                                accurate_freq_avail = 1;
                            }
                        }
                    }

                    cpu_chart->st = rrdset_create_localhost(
                            type
                            , id
                            , NULL
                            , family
                            , context
                            , title
                            , "percentage"
                            , PLUGIN_PROC_NAME
                            , PLUGIN_PROC_MODULE_STAT_NAME
                            , priority + core
                            , update_every
                            , RRDSET_TYPE_STACKED
                    );

                    long multiplier = 1;
                    long divisor = 1; // sysconf(_SC_CLK_TCK);

                    cpu_chart->rd_guest_nice = rrddim_add(cpu_chart->st, "guest_nice", NULL, multiplier, divisor, RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL);
                    cpu_chart->rd_guest      = rrddim_add(cpu_chart->st, "guest",      NULL, multiplier, divisor, RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL);
                    cpu_chart->rd_steal      = rrddim_add(cpu_chart->st, "steal",      NULL, multiplier, divisor, RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL);
                    cpu_chart->rd_softirq    = rrddim_add(cpu_chart->st, "softirq",    NULL, multiplier, divisor, RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL);
                    cpu_chart->rd_irq        = rrddim_add(cpu_chart->st, "irq",        NULL, multiplier, divisor, RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL);
                    cpu_chart->rd_user       = rrddim_add(cpu_chart->st, "user",       NULL, multiplier, divisor, RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL);
                    cpu_chart->rd_system     = rrddim_add(cpu_chart->st, "system",     NULL, multiplier, divisor, RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL);
                    cpu_chart->rd_nice       = rrddim_add(cpu_chart->st, "nice",       NULL, multiplier, divisor, RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL);
                    cpu_chart->rd_iowait     = rrddim_add(cpu_chart->st, "iowait",     NULL, multiplier, divisor, RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL);
                    cpu_chart->rd_idle       = rrddim_add(cpu_chart->st, "idle",       NULL, multiplier, divisor, RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL);
                    rrddim_hide(cpu_chart->st, "idle");

                    if(unlikely(core == 0 && cpus_var == NULL))
                        cpus_var = rrdvar_custom_host_variable_create(localhost, "active_processors");
                }
                else rrdset_next(cpu_chart->st);

                rrddim_set_by_pointer(cpu_chart->st, cpu_chart->rd_user, user);
                rrddim_set_by_pointer(cpu_chart->st, cpu_chart->rd_nice, nice);
                rrddim_set_by_pointer(cpu_chart->st, cpu_chart->rd_system, system);
                rrddim_set_by_pointer(cpu_chart->st, cpu_chart->rd_idle, idle);
                rrddim_set_by_pointer(cpu_chart->st, cpu_chart->rd_iowait, iowait);
                rrddim_set_by_pointer(cpu_chart->st, cpu_chart->rd_irq, irq);
                rrddim_set_by_pointer(cpu_chart->st, cpu_chart->rd_softirq, softirq);
                rrddim_set_by_pointer(cpu_chart->st, cpu_chart->rd_steal, steal);
                rrddim_set_by_pointer(cpu_chart->st, cpu_chart->rd_guest, guest);
                rrddim_set_by_pointer(cpu_chart->st, cpu_chart->rd_guest_nice, guest_nice);
                rrdset_done(cpu_chart->st);
            }
        }
        else if(unlikely(hash == hash_intr && strcmp(row_key, "intr") == 0)) {
            if(likely(do_interrupts)) {
                static RRDSET *st_intr = NULL;
                static RRDDIM *rd_interrupts = NULL;
                unsigned long long value = str2ull(procfile_lineword(ff, l, 1));

                if(unlikely(!st_intr)) {
                    st_intr = rrdset_create_localhost(
                            "system"
                            , "intr"
                            , NULL
                            , "interrupts"
                            , NULL
                            , "CPU Interrupts"
                            , "interrupts/s"
                            , PLUGIN_PROC_NAME
                            , PLUGIN_PROC_MODULE_STAT_NAME
                            , NETDATA_CHART_PRIO_SYSTEM_INTR
                            , update_every
                            , RRDSET_TYPE_LINE
                    );

                    rrdset_flag_set(st_intr, RRDSET_FLAG_DETAIL);

                    rd_interrupts = rrddim_add(st_intr, "interrupts", NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
                }
                else rrdset_next(st_intr);

                rrddim_set_by_pointer(st_intr, rd_interrupts, value);
                rrdset_done(st_intr);
            }
        }
        else if(unlikely(hash == hash_ctxt && strcmp(row_key, "ctxt") == 0)) {
            if(likely(do_context)) {
                static RRDSET *st_ctxt = NULL;
                static RRDDIM *rd_switches = NULL;
                unsigned long long value = str2ull(procfile_lineword(ff, l, 1));

                if(unlikely(!st_ctxt)) {
                    st_ctxt = rrdset_create_localhost(
                            "system"
                            , "ctxt"
                            , NULL
                            , "processes"
                            , NULL
                            , "CPU Context Switches"
                            , "context switches/s"
                            , PLUGIN_PROC_NAME
                            , PLUGIN_PROC_MODULE_STAT_NAME
                            , NETDATA_CHART_PRIO_SYSTEM_CTXT
                            , update_every
                            , RRDSET_TYPE_LINE
                    );

                    rd_switches = rrddim_add(st_ctxt, "switches", NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
                }
                else rrdset_next(st_ctxt);

                rrddim_set_by_pointer(st_ctxt, rd_switches, value);
                rrdset_done(st_ctxt);
            }
        }
        else if(unlikely(hash == hash_processes && !processes && strcmp(row_key, "processes") == 0)) {
            processes = str2ull(procfile_lineword(ff, l, 1));
        }
        else if(unlikely(hash == hash_procs_running && !running && strcmp(row_key, "procs_running") == 0)) {
            running = str2ull(procfile_lineword(ff, l, 1));
        }
        else if(unlikely(hash == hash_procs_blocked && !blocked && strcmp(row_key, "procs_blocked") == 0)) {
            blocked = str2ull(procfile_lineword(ff, l, 1));
        }
    }

    // --------------------------------------------------------------------

    if(likely(do_forks)) {
        static RRDSET *st_forks = NULL;
        static RRDDIM *rd_started = NULL;

        if(unlikely(!st_forks)) {
            st_forks = rrdset_create_localhost(
                    "system"
                    , "forks"
                    , NULL
                    , "processes"
                    , NULL
                    , "Started Processes"
                    , "processes/s"
                    , PLUGIN_PROC_NAME
                    , PLUGIN_PROC_MODULE_STAT_NAME
                    , NETDATA_CHART_PRIO_SYSTEM_FORKS
                    , update_every
                    , RRDSET_TYPE_LINE
            );
            rrdset_flag_set(st_forks, RRDSET_FLAG_DETAIL);

            rd_started = rrddim_add(st_forks, "started", NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
        }
        else rrdset_next(st_forks);

        rrddim_set_by_pointer(st_forks, rd_started, processes);
        rrdset_done(st_forks);
    }

    // --------------------------------------------------------------------

    if(likely(do_processes)) {
        static RRDSET *st_processes = NULL;
        static RRDDIM *rd_running = NULL;
        static RRDDIM *rd_blocked = NULL;

        if(unlikely(!st_processes)) {
            st_processes = rrdset_create_localhost(
                    "system"
                    , "processes"
                    , NULL
                    , "processes"
                    , NULL
                    , "System Processes"
                    , "processes"
                    , PLUGIN_PROC_NAME
                    , PLUGIN_PROC_MODULE_STAT_NAME
                    , NETDATA_CHART_PRIO_SYSTEM_PROCESSES
                    , update_every
                    , RRDSET_TYPE_LINE
            );

            rd_running = rrddim_add(st_processes, "running", NULL, 1, 1, RRD_ALGORITHM_ABSOLUTE);
            rd_blocked = rrddim_add(st_processes, "blocked", NULL, -1, 1, RRD_ALGORITHM_ABSOLUTE);
        }
        else rrdset_next(st_processes);

        rrddim_set_by_pointer(st_processes, rd_running, running);
        rrddim_set_by_pointer(st_processes, rd_blocked, blocked);
        rrdset_done(st_processes);
    }

    if(likely(all_cpu_charts_size > 1)) {
        if(likely(do_core_throttle_count != CONFIG_BOOLEAN_NO)) {
            int r = read_per_core_files(&all_cpu_charts[1], all_cpu_charts_size - 1, CORE_THROTTLE_COUNT_INDEX);
            if(likely(r != -1 && (do_core_throttle_count == CONFIG_BOOLEAN_YES || r > 0))) {
                do_core_throttle_count = CONFIG_BOOLEAN_YES;

                static RRDSET *st_core_throttle_count = NULL;

                if (unlikely(!st_core_throttle_count))
                    st_core_throttle_count = rrdset_create_localhost(
                            "cpu"
                            , "core_throttling"
                            , NULL
                            , "throttling"
                            , "cpu.core_throttling"
                            , "Core Thermal Throttling Events"
                            , "events/s"
                            , PLUGIN_PROC_NAME
                            , PLUGIN_PROC_MODULE_STAT_NAME
                            , NETDATA_CHART_PRIO_CORE_THROTTLING
                            , update_every
                            , RRDSET_TYPE_LINE
                    );
                else
                    rrdset_next(st_core_throttle_count);

                chart_per_core_files(&all_cpu_charts[1], all_cpu_charts_size - 1, CORE_THROTTLE_COUNT_INDEX, st_core_throttle_count, 1, 1, RRD_ALGORITHM_INCREMENTAL);
                rrdset_done(st_core_throttle_count);
            }
        }

        if(likely(do_package_throttle_count != CONFIG_BOOLEAN_NO)) {
            int r = read_per_core_files(&all_cpu_charts[1], all_cpu_charts_size - 1, PACKAGE_THROTTLE_COUNT_INDEX);
            if(likely(r != -1 && (do_package_throttle_count == CONFIG_BOOLEAN_YES || r > 0))) {
                do_package_throttle_count = CONFIG_BOOLEAN_YES;

                static RRDSET *st_package_throttle_count = NULL;

                if(unlikely(!st_package_throttle_count))
                    st_package_throttle_count = rrdset_create_localhost(
                            "cpu"
                            , "package_throttling"
                            , NULL
                            , "throttling"
                            , "cpu.package_throttling"
                            , "Package Thermal Throttling Events"
                            , "events/s"
                            , PLUGIN_PROC_NAME
                            , PLUGIN_PROC_MODULE_STAT_NAME
                            , NETDATA_CHART_PRIO_PACKAGE_THROTTLING
                            , update_every
                            , RRDSET_TYPE_LINE
                    );
                else
                    rrdset_next(st_package_throttle_count);

                chart_per_core_files(&all_cpu_charts[1], all_cpu_charts_size - 1, PACKAGE_THROTTLE_COUNT_INDEX, st_package_throttle_count, 1, 1, RRD_ALGORITHM_INCREMENTAL);
                rrdset_done(st_package_throttle_count);
            }
        }

        if(likely(do_cpu_freq != CONFIG_BOOLEAN_NO)) {
            char filename[FILENAME_MAX + 1];
            int r = 0;

            if (accurate_freq_avail) {
                r = read_per_core_time_in_state_files(&all_cpu_charts[1], all_cpu_charts_size - 1, CPU_FREQ_INDEX);
                if(r > 0 && !accurate_freq_is_used) {
                    accurate_freq_is_used = 1;
                    snprintfz(filename, FILENAME_MAX, time_in_state_filename, "cpu*");
                    info("cpufreq is using %s", filename);
                }
            }
            if (r < 1) {
                r = read_per_core_files(&all_cpu_charts[1], all_cpu_charts_size - 1, CPU_FREQ_INDEX);
                if(accurate_freq_is_used) {
                    accurate_freq_is_used = 0;
                    snprintfz(filename, FILENAME_MAX, scaling_cur_freq_filename, "cpu*");
                    info("cpufreq fell back to %s", filename);
                }
            }

            if(likely(r != -1 && (do_cpu_freq == CONFIG_BOOLEAN_YES || r > 0))) {
                do_cpu_freq = CONFIG_BOOLEAN_YES;

                static RRDSET *st_scaling_cur_freq = NULL;

                if(unlikely(!st_scaling_cur_freq))
                    st_scaling_cur_freq = rrdset_create_localhost(
                            "cpu"
                            , "cpufreq"
                            , NULL
                            , "cpufreq"
                            , "cpufreq.cpufreq"
                            , "Current CPU Frequency"
                            , "MHz"
                            , PLUGIN_PROC_NAME
                            , PLUGIN_PROC_MODULE_STAT_NAME
                            , NETDATA_CHART_PRIO_CPUFREQ_SCALING_CUR_FREQ
                            , update_every
                            , RRDSET_TYPE_LINE
                    );
                else
                    rrdset_next(st_scaling_cur_freq);

                chart_per_core_files(&all_cpu_charts[1], all_cpu_charts_size - 1, CPU_FREQ_INDEX, st_scaling_cur_freq, 1, 1000, RRD_ALGORITHM_ABSOLUTE);
                rrdset_done(st_scaling_cur_freq);
            }
        }
    }

    // --------------------------------------------------------------------

    static struct per_core_cpuidle_chart *cpuidle_charts = NULL;
    size_t schedstat_cores_found = 0;

    if(likely(do_cpuidle != CONFIG_BOOLEAN_NO && !read_schedstat(schedstat_filename, &cpuidle_charts, &schedstat_cores_found))) {
        int cpu_states_updated = 0;
        size_t core, state;


        // proc.plugin runs on Linux systems only. Multi-platform compatibility is not needed here,
        // so bare pthread functions are used to avoid unneeded overheads.
        for(core = 0; core < schedstat_cores_found; core++) {
            if(unlikely(!(cpuidle_charts[core].active_time - cpuidle_charts[core].last_active_time))) {
                pthread_t thread;

                if(unlikely(pthread_create(&thread, NULL, wake_cpu_thread, (void *)&core)))
                    error("Cannot create wake_cpu_thread");
                else if(unlikely(pthread_join(thread, NULL)))
                    error("Cannot join wake_cpu_thread");
                cpu_states_updated = 1;
            }
        }

        if(unlikely(!cpu_states_updated || !read_schedstat(schedstat_filename, &cpuidle_charts, &schedstat_cores_found))) {
            for(core = 0; core < schedstat_cores_found; core++) {
                cpuidle_charts[core].last_active_time = cpuidle_charts[core].active_time;

                int r = read_cpuidle_states(cpuidle_name_filename, cpuidle_time_filename, cpuidle_charts, core);
                if(likely(r != -1 && (do_cpuidle == CONFIG_BOOLEAN_YES || r > 0))) {
                    do_cpuidle = CONFIG_BOOLEAN_YES;

                    char cpuidle_chart_id[RRD_ID_LENGTH_MAX + 1];
                    snprintfz(cpuidle_chart_id, RRD_ID_LENGTH_MAX, "cpu%zu_cpuidle", core);

                    if(unlikely(!cpuidle_charts[core].st)) {
                        cpuidle_charts[core].st = rrdset_create_localhost(
                                "cpu"
                                , cpuidle_chart_id
                                , NULL
                                , "cpuidle"
                                , "cpuidle.cpuidle"
                                , "C-state residency time"
                                , "percentage"
                                , PLUGIN_PROC_NAME
                                , PLUGIN_PROC_MODULE_STAT_NAME
                                , NETDATA_CHART_PRIO_CPUIDLE + core
                                , update_every
                                , RRDSET_TYPE_STACKED
                        );

                        char cpuidle_dim_id[RRD_ID_LENGTH_MAX + 1];
                        snprintfz(cpuidle_dim_id, RRD_ID_LENGTH_MAX, "cpu%zu_active_time", core);
                        cpuidle_charts[core].active_time_rd = rrddim_add(cpuidle_charts[core].st, cpuidle_dim_id, "C0 (active)", 1, 1, RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL);
                        for(state = 0; state < cpuidle_charts[core].cpuidle_state_len; state++) {
                            snprintfz(cpuidle_dim_id, RRD_ID_LENGTH_MAX, "cpu%zu_cpuidle_state%zu_time", core, state);
                            cpuidle_charts[core].cpuidle_state[state].rd = rrddim_add(cpuidle_charts[core].st, cpuidle_dim_id,
                                                                                      cpuidle_charts[core].cpuidle_state[state].name,
                                                                                      1, 1, RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL);
                        }
                    }
                    else
                        rrdset_next(cpuidle_charts[core].st);

                    rrddim_set_by_pointer(cpuidle_charts[core].st, cpuidle_charts[core].active_time_rd, cpuidle_charts[core].active_time);
                    for(state = 0; state < cpuidle_charts[core].cpuidle_state_len; state++) {
                        rrddim_set_by_pointer(cpuidle_charts[core].st, cpuidle_charts[core].cpuidle_state[state].rd, cpuidle_charts[core].cpuidle_state[state].value);
                    }
                    rrdset_done(cpuidle_charts[core].st);
                }
            }
        }
    }

    if(cpus_var)
        rrdvar_custom_host_variable_set(localhost, cpus_var, cores_found);

    return 0;
}