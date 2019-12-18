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
typedef  int usec_t ;
typedef  char* uid_t ;
typedef  int time_t ;
struct rlimit {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct pid_stat {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  heartbeat_t ;
struct TYPE_4__ {int filename; } ;
struct TYPE_3__ {int filename; } ;

/* Variables and functions */
 int /*<<< orphan*/ * CONFIG_DIR ; 
 int /*<<< orphan*/  FILENAME_MAX ; 
 int /*<<< orphan*/ * LIBCONFIG_DIR ; 
 int O_NOFOLLOW ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  PR_SET_DUMPABLE ; 
 unsigned long long RATES_DETAIL ; 
 int /*<<< orphan*/  RLIMIT_CORE ; 
 int /*<<< orphan*/  RLIM_INFINITY ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 TYPE_2__ all_group_ids ; 
 void* all_pids ; 
 void* all_pids_sortlist ; 
 TYPE_1__ all_user_ids ; 
 int /*<<< orphan*/  am_i_running_as_root () ; 
 int /*<<< orphan*/  apps_groups_root_target ; 
 int /*<<< orphan*/  calculate_netdata_statistics () ; 
 void* callocz (int,size_t) ; 
 int /*<<< orphan*/  check_capabilities () ; 
 int /*<<< orphan*/  check_proc_1_io () ; 
 int /*<<< orphan*/  collect_data_for_all_processes () ; 
 scalar_t__ debug_flags ; 
 int /*<<< orphan*/  debug_log (char*,int) ; 
 int /*<<< orphan*/  enable_groups_charts ; 
 int /*<<< orphan*/  enable_users_charts ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int error_log_errors_per_period ; 
 scalar_t__ error_log_syslog ; 
 int error_log_throttle_period ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_system_HZ () ; 
 int /*<<< orphan*/  get_system_cpus () ; 
 int /*<<< orphan*/  get_system_pid_max () ; 
 void* getenv (char*) ; 
 char* geteuid () ; 
 int /*<<< orphan*/  getpid () ; 
 char* getuid () ; 
 int global_iterations_counter ; 
 int /*<<< orphan*/  groups_root_target ; 
 int /*<<< orphan*/  heartbeat_init (int /*<<< orphan*/ *) ; 
 int heartbeat_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  info (char*,...) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 void* netdata_configured_host_prefix ; 
 int /*<<< orphan*/  normalize_utilization (int /*<<< orphan*/ ) ; 
 int now_monotonic_sec () ; 
 size_t pagesize ; 
 int /*<<< orphan*/  parse_args (int,char**) ; 
 scalar_t__ pid_max ; 
 int /*<<< orphan*/  prctl (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int procfile_adaptive_initial_allocation ; 
 int procfile_open_flags ; 
 char* program_name ; 
 int /*<<< orphan*/  send_charts_updates_to_netdata (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  send_collected_data_to_netdata (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  send_resource_usage_to_netdata (int) ; 
 scalar_t__ setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  show_guest_time ; 
 int /*<<< orphan*/  show_guest_time_old ; 
 int /*<<< orphan*/  snprintfz (int,int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/ * stock_config_dir ; 
 scalar_t__ sysconf (int /*<<< orphan*/ ) ; 
 unsigned long long system_hz ; 
 unsigned long long time_factor ; 
 scalar_t__ unlikely (int) ; 
 int update_every ; 
 int /*<<< orphan*/ * user_config_dir ; 
 int /*<<< orphan*/  users_root_target ; 
 int verify_netdata_host_prefix () ; 

int main(int argc, char **argv) {
    // debug_flags = D_PROCFILE;

    pagesize = (size_t)sysconf(_SC_PAGESIZE);

    // set the name for logging
    program_name = "apps.plugin";

    // disable syslog for apps.plugin
    error_log_syslog = 0;

    // set errors flood protection to 100 logs per hour
    error_log_errors_per_period = 100;
    error_log_throttle_period = 3600;

    // since apps.plugin runs as root, prevent it from opening symbolic links
    procfile_open_flags = O_RDONLY|O_NOFOLLOW;

    netdata_configured_host_prefix = getenv("NETDATA_HOST_PREFIX");
    if(verify_netdata_host_prefix() == -1) exit(1);

    user_config_dir = getenv("NETDATA_USER_CONFIG_DIR");
    if(user_config_dir == NULL) {
        // info("NETDATA_CONFIG_DIR is not passed from netdata");
        user_config_dir = CONFIG_DIR;
    }
    // else info("Found NETDATA_USER_CONFIG_DIR='%s'", user_config_dir);

    stock_config_dir = getenv("NETDATA_STOCK_CONFIG_DIR");
    if(stock_config_dir == NULL) {
        // info("NETDATA_CONFIG_DIR is not passed from netdata");
        stock_config_dir = LIBCONFIG_DIR;
    }
    // else info("Found NETDATA_USER_CONFIG_DIR='%s'", user_config_dir);

#ifdef NETDATA_INTERNAL_CHECKS
    if(debug_flags != 0) {
        struct rlimit rl = { RLIM_INFINITY, RLIM_INFINITY };
        if(setrlimit(RLIMIT_CORE, &rl) != 0)
            info("Cannot request unlimited core dumps for debugging... Proceeding anyway...");
#ifdef HAVE_SYS_PRCTL_H
        prctl(PR_SET_DUMPABLE, 1, 0, 0, 0);
#endif
    }
#endif /* NETDATA_INTERNAL_CHECKS */

    procfile_adaptive_initial_allocation = 1;

    time_t started_t = now_monotonic_sec();

    get_system_HZ();
#ifdef __FreeBSD__
    time_factor = 1000000ULL / RATES_DETAIL; // FreeBSD uses usecs
#else
    time_factor = system_hz; // Linux uses clock ticks
#endif

    get_system_pid_max();
    get_system_cpus();

    parse_args(argc, argv);

    if(!check_capabilities() && !am_i_running_as_root() && !check_proc_1_io()) {
        uid_t uid = getuid(), euid = geteuid();
#ifdef HAVE_CAPABILITY
        error("apps.plugin should either run as root (now running with uid %u, euid %u) or have special capabilities. "
                      "Without these, apps.plugin cannot report disk I/O utilization of other processes. "
                      "To enable capabilities run: sudo setcap cap_dac_read_search,cap_sys_ptrace+ep %s; "
                      "To enable setuid to root run: sudo chown root:netdata %s; sudo chmod 4750 %s; "
              , uid, euid, argv[0], argv[0], argv[0]
        );
#else
        error("apps.plugin should either run as root (now running with uid %u, euid %u) or have special capabilities. "
                      "Without these, apps.plugin cannot report disk I/O utilization of other processes. "
                      "Your system does not support capabilities. "
                      "To enable setuid to root run: sudo chown root:netdata %s; sudo chmod 4750 %s; "
              , uid, euid, argv[0], argv[0]
        );
#endif
    }

    info("started on pid %d", getpid());

    snprintfz(all_user_ids.filename, FILENAME_MAX, "%s/etc/passwd", netdata_configured_host_prefix);
    debug_log("passwd file: '%s'", all_user_ids.filename);

    snprintfz(all_group_ids.filename, FILENAME_MAX, "%s/etc/group", netdata_configured_host_prefix);
    debug_log("group file: '%s'", all_group_ids.filename);

#if (ALL_PIDS_ARE_READ_INSTANTLY == 0)
    all_pids_sortlist = callocz(sizeof(pid_t), (size_t)pid_max);
#endif

    all_pids          = callocz(sizeof(struct pid_stat *), (size_t) pid_max);

    usec_t step = update_every * USEC_PER_SEC;
    global_iterations_counter = 1;
    heartbeat_t hb;
    heartbeat_init(&hb);
    for(;1; global_iterations_counter++) {

#ifdef NETDATA_PROFILING
#warning "compiling for profiling"
        static int profiling_count=0;
        profiling_count++;
        if(unlikely(profiling_count > 2000)) exit(0);
        usec_t dt = update_every * USEC_PER_SEC;
#else
        usec_t dt = heartbeat_next(&hb, step);
#endif

        if(!collect_data_for_all_processes()) {
            error("Cannot collect /proc data for running processes. Disabling apps.plugin...");
            printf("DISABLE\n");
            exit(1);
        }

        calculate_netdata_statistics();
        normalize_utilization(apps_groups_root_target);

        send_resource_usage_to_netdata(dt);

        // this is smart enough to show only newly added apps, when needed
        send_charts_updates_to_netdata(apps_groups_root_target, "apps", "Apps");

        if(likely(enable_users_charts))
            send_charts_updates_to_netdata(users_root_target, "users", "Users");

        if(likely(enable_groups_charts))
            send_charts_updates_to_netdata(groups_root_target, "groups", "User Groups");

        send_collected_data_to_netdata(apps_groups_root_target, "apps", dt);

        if(likely(enable_users_charts))
            send_collected_data_to_netdata(users_root_target, "users", dt);

        if(likely(enable_groups_charts))
            send_collected_data_to_netdata(groups_root_target, "groups", dt);

        fflush(stdout);

        show_guest_time_old = show_guest_time;

        debug_log("done Loop No %zu", global_iterations_counter);

        // restart check (14400 seconds)
        if(now_monotonic_sec() - started_t > 14400) exit(0);
    }
}