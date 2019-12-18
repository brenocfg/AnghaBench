#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pollfd {int fd; scalar_t__ revents; int /*<<< orphan*/  events; } ;
struct option {char* member_0; char member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  const member_1; } ;
struct TYPE_2__ {int operation; } ;
struct hv_vss_msg {int error; TYPE_1__ vss_hdr; } ;
typedef  int /*<<< orphan*/  kernel_modver ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int EXIT_FAILURE ; 
 int HV_E_FAIL ; 
 int HV_S_OK ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_USER ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  POLLIN ; 
#define  VSS_OP_FREEZE 131 
#define  VSS_OP_HOT_BACKUP 130 
 int VSS_OP_REGISTER1 ; 
#define  VSS_OP_THAW 129 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ daemon (int,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt_long (int,char**,char*,struct option*,int*) ; 
 int /*<<< orphan*/  getpid () ; 
#define  no_argument 128 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openlog (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  print_usage (char**) ; 
 int read (int,struct hv_vss_msg*,int) ; 
 char* strerror (scalar_t__) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 
 int vss_operate (int const) ; 
 int write (int,struct hv_vss_msg*,int) ; 

int main(int argc, char *argv[])
{
	int vss_fd, len;
	int error;
	struct pollfd pfd;
	int	op;
	struct hv_vss_msg vss_msg[1];
	int daemonize = 1, long_index = 0, opt;
	int in_handshake = 1;
	__u32 kernel_modver;

	static struct option long_options[] = {
		{"help",	no_argument,	   0,  'h' },
		{"no-daemon",	no_argument,	   0,  'n' },
		{0,		0,		   0,  0   }
	};

	while ((opt = getopt_long(argc, argv, "hn", long_options,
				  &long_index)) != -1) {
		switch (opt) {
		case 'n':
			daemonize = 0;
			break;
		case 'h':
			print_usage(argv);
			exit(0);
		default:
			print_usage(argv);
			exit(EXIT_FAILURE);
		}
	}

	if (daemonize && daemon(1, 0))
		return 1;

	openlog("Hyper-V VSS", 0, LOG_USER);
	syslog(LOG_INFO, "VSS starting; pid is:%d", getpid());

	vss_fd = open("/dev/vmbus/hv_vss", O_RDWR);
	if (vss_fd < 0) {
		syslog(LOG_ERR, "open /dev/vmbus/hv_vss failed; error: %d %s",
		       errno, strerror(errno));
		exit(EXIT_FAILURE);
	}
	/*
	 * Register ourselves with the kernel.
	 */
	vss_msg->vss_hdr.operation = VSS_OP_REGISTER1;

	len = write(vss_fd, vss_msg, sizeof(struct hv_vss_msg));
	if (len < 0) {
		syslog(LOG_ERR, "registration to kernel failed; error: %d %s",
		       errno, strerror(errno));
		close(vss_fd);
		exit(EXIT_FAILURE);
	}

	pfd.fd = vss_fd;

	while (1) {
		pfd.events = POLLIN;
		pfd.revents = 0;

		if (poll(&pfd, 1, -1) < 0) {
			syslog(LOG_ERR, "poll failed; error:%d %s", errno, strerror(errno));
			if (errno == EINVAL) {
				close(vss_fd);
				exit(EXIT_FAILURE);
			}
			else
				continue;
		}

		len = read(vss_fd, vss_msg, sizeof(struct hv_vss_msg));

		if (in_handshake) {
			if (len != sizeof(kernel_modver)) {
				syslog(LOG_ERR, "invalid version negotiation");
				exit(EXIT_FAILURE);
			}
			kernel_modver = *(__u32 *)vss_msg;
			in_handshake = 0;
			syslog(LOG_INFO, "VSS: kernel module version: %d",
			       kernel_modver);
			continue;
		}

		if (len != sizeof(struct hv_vss_msg)) {
			syslog(LOG_ERR, "read failed; error:%d %s",
			       errno, strerror(errno));
			close(vss_fd);
			return EXIT_FAILURE;
		}

		op = vss_msg->vss_hdr.operation;
		error =  HV_S_OK;

		switch (op) {
		case VSS_OP_FREEZE:
		case VSS_OP_THAW:
			error = vss_operate(op);
			syslog(LOG_INFO, "VSS: op=%s: %s\n",
				op == VSS_OP_FREEZE ? "FREEZE" : "THAW",
				error ? "failed" : "succeeded");

			if (error) {
				error = HV_E_FAIL;
				syslog(LOG_ERR, "op=%d failed!", op);
				syslog(LOG_ERR, "report it with these files:");
				syslog(LOG_ERR, "/etc/fstab and /proc/mounts");
			}
			break;
		case VSS_OP_HOT_BACKUP:
			syslog(LOG_INFO, "VSS: op=CHECK HOT BACKUP\n");
			break;
		default:
			syslog(LOG_ERR, "Illegal op:%d\n", op);
		}
		vss_msg->error = error;
		len = write(vss_fd, vss_msg, sizeof(struct hv_vss_msg));
		if (len != sizeof(struct hv_vss_msg)) {
			syslog(LOG_ERR, "write failed; error: %d %s", errno,
			       strerror(errno));

			if (op == VSS_OP_FREEZE)
				vss_operate(VSS_OP_THAW);
		}
	}

	close(vss_fd);
	exit(0);
}