#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int we_wordc; char** we_wordv; } ;
typedef  TYPE_1__ wordexp_t ;
struct winsize {int dummy; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  endwin () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ flag_monitor ; 
 scalar_t__ flag_monitor_continuous ; 
 int flag_throughput ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/ * initscr () ; 
 int /*<<< orphan*/  int_handler ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct winsize*) ; 
 int /*<<< orphan*/ * mainwin ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  monitor_processes (scalar_t__*) ; 
 int /*<<< orphan*/  parse_options (int,char**) ; 
 int /*<<< orphan*/  populate_proc_names () ; 
 int /*<<< orphan*/  refresh () ; 
 int /*<<< orphan*/  set_hlist_size (int) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 int throughput_wait_secs ; 
 int /*<<< orphan*/  usleep (int) ; 
 scalar_t__ wordexp (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[])
{
pid_t nb_pid;
struct winsize ws;
wordexp_t env_wordexp;
char *env_progress_args;
char *env_progress_args_full;

populate_proc_names();

env_progress_args = getenv("PROGRESS_ARGS");

if (env_progress_args) {
    int full_len;

    // prefix with (real) argv[0]
    // argv[0] + ' ' + env_progress_args + '\0'
    full_len = strlen(argv[0]) + 1 + strlen(env_progress_args) + 1;
    env_progress_args_full = malloc(full_len * sizeof(char));
    assert(env_progress_args_full != NULL);
    sprintf(env_progress_args_full, "%s %s", argv[0], env_progress_args);

    if (wordexp(env_progress_args_full, &env_wordexp, 0)) {
        fprintf(stderr,"Unable to parse PROGRESS_ARGS environment variable.\n");
        exit(EXIT_FAILURE);
    }
    parse_options(env_wordexp.we_wordc,env_wordexp.we_wordv);
}
parse_options(argc,argv);

// ws.ws_row, ws.ws_col
ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
if (flag_monitor || flag_monitor_continuous) {
    setlocale(LC_CTYPE, "");
    if ((mainwin = initscr()) == NULL ) {
        fprintf(stderr, "Error initialising ncurses.\n");
        exit(EXIT_FAILURE);
    }
    if (!flag_throughput) {
      flag_throughput = 1;
      throughput_wait_secs = 1;
    }
    set_hlist_size(throughput_wait_secs);
    signal(SIGINT, int_handler);
    do {
        monitor_processes(&nb_pid);
        refresh();
        if(flag_monitor_continuous && !nb_pid) {
          usleep(1000000 * throughput_wait_secs);
        }
    } while ((flag_monitor && nb_pid) || flag_monitor_continuous);
    endwin();
}
else {
    set_hlist_size(throughput_wait_secs);
    monitor_processes(&nb_pid);
}
return 0;
}