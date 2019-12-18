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
typedef  int /*<<< orphan*/  u16_t ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct ead_instance {int /*<<< orphan*/  id; int /*<<< orphan*/  list; int /*<<< orphan*/  ifname; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int /*<<< orphan*/  O_RDWR ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  br_init () ; 
 int /*<<< orphan*/  br_shutdown () ; 
 int /*<<< orphan*/  check_all_interfaces () ; 
 int /*<<< orphan*/  close (int) ; 
 void* dev_name ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 scalar_t__ ethmac ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_random_bytes (scalar_t__,int) ; 
 int getopt (int,char**,char*) ; 
 int getpid () ; 
 int /*<<< orphan*/  instances ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ead_instance* malloc (int) ; 
 int /*<<< orphan*/  memset (struct ead_instance*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nid ; 
 int nonfork ; 
 int open (char const*,int,...) ; 
 void* optarg ; 
 void* passwd_file ; 
 int /*<<< orphan*/  server_handle_sigchld ; 
 int /*<<< orphan*/  server_handle_sigint ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  start_servers (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  unlink (char const*) ; 
 int usage (char*) ; 
 int /*<<< orphan*/  write (int,char*,int) ; 

int main(int argc, char **argv)
{
	struct ead_instance *in;
	struct timeval tv;
	const char *pidfile = NULL;
	bool background = false;
	int n_iface = 0;
	int fd, ch;

	if (argc == 1)
		return usage(argv[0]);

	INIT_LIST_HEAD(&instances);
	while ((ch = getopt(argc, argv, "Bd:D:fhp:P:")) != -1) {
		switch(ch) {
		case 'B':
			background = true;
			break;
		case 'f':
			nonfork = true;
			break;
		case 'h':
			return usage(argv[0]);
		case 'd':
			in = malloc(sizeof(struct ead_instance));
			memset(in, 0, sizeof(struct ead_instance));
			INIT_LIST_HEAD(&in->list);
			strncpy(in->ifname, optarg, sizeof(in->ifname) - 1);
			list_add(&in->list, &instances);
			in->id = n_iface++;
			break;
		case 'D':
			dev_name = optarg;
			break;
		case 'p':
			passwd_file = optarg;
			break;
		case 'P':
			pidfile = optarg;
			break;
		}
	}
	signal(SIGCHLD, server_handle_sigchld);
	signal(SIGINT, server_handle_sigint);
	signal(SIGTERM, server_handle_sigint);
	signal(SIGKILL, server_handle_sigint);

	if (!n_iface) {
		fprintf(stderr, "Error: ead needs at least one interface\n");
		return -1;
	}

	if (background) {
		if (fork() > 0)
			exit(0);

		fd = open("/dev/null", O_RDWR);
		dup2(fd, 0);
		dup2(fd, 1);
		dup2(fd, 2);
	}

	if (pidfile) {
		char pid[8];
		int len;

		unlink(pidfile);
		fd = open(pidfile, O_CREAT|O_WRONLY|O_EXCL, 0644);
		if (fd > 0) {
			len = sprintf(pid, "%d\n", getpid());
			write(fd, pid, len);
			close(fd);
		}
	}

	/* randomize the mac address */
	get_random_bytes(ethmac + 3, 3);
	nid = *(((u16_t *) ethmac) + 2);

	start_servers(false);
	br_init();
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	while (1) {
		check_all_interfaces();
		start_servers(true);
		sleep(1);
	}
	br_shutdown();

	return 0;
}