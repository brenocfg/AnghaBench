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
struct stat {int dummy; } ;
struct sched_param {int /*<<< orphan*/  sched_priority; } ;
typedef  int /*<<< orphan*/  count ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int EINVAL ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int LOG_CONS ; 
 int /*<<< orphan*/  LOG_LOCAL1 ; 
 int LOG_NDELAY ; 
 int LOG_PID ; 
 int MCL_CURRENT ; 
 int MCL_FUTURE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SCHED_FIFO ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  alarm (int) ; 
 int /*<<< orphan*/  app_name ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closelog () ; 
 scalar_t__ daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ignore_me ; 
 scalar_t__ lid_open () ; 
 int /*<<< orphan*/  mlockall (int) ; 
 int noled ; 
 scalar_t__ on_ac () ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openlog (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  protect (int) ; 
 int read (int,unsigned char*,int) ; 
 int /*<<< orphan*/  sched_get_priority_max (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_setscheduler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sched_param*) ; 
 int /*<<< orphan*/  set_led (int) ; 
 int set_unload_heads_path (char*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  valid_disk () ; 

int main(int argc, char **argv)
{
	int fd, ret;
	struct stat st;
	struct sched_param param;

	if (argc == 1)
		ret = set_unload_heads_path("/dev/sda");
	else if (argc == 2)
		ret = set_unload_heads_path(argv[1]);
	else
		ret = -EINVAL;

	if (ret || !valid_disk()) {
		fprintf(stderr, "usage: %s <device> (default: /dev/sda)\n",
				argv[0]);
		exit(1);
	}

	fd = open("/dev/freefall", O_RDONLY);
	if (fd < 0) {
		perror("/dev/freefall");
		return EXIT_FAILURE;
	}

	if (stat("/sys/class/leds/hp::hddprotect/brightness", &st))
		noled = 1;

	if (daemon(0, 0) != 0) {
		perror("daemon");
		return EXIT_FAILURE;
	}

	openlog(app_name, LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

	param.sched_priority = sched_get_priority_max(SCHED_FIFO);
	sched_setscheduler(0, SCHED_FIFO, &param);
	mlockall(MCL_CURRENT|MCL_FUTURE);

	signal(SIGALRM, ignore_me);

	for (;;) {
		unsigned char count;

		ret = read(fd, &count, sizeof(count));
		alarm(0);
		if ((ret == -1) && (errno == EINTR)) {
			/* Alarm expired, time to unpark the heads */
			continue;
		}

		if (ret != sizeof(count)) {
			perror("read");
			break;
		}

		protect(21);
		set_led(1);
		if (1 || on_ac() || lid_open())
			alarm(2);
		else
			alarm(20);
	}

	closelog();
	close(fd);
	return EXIT_SUCCESS;
}