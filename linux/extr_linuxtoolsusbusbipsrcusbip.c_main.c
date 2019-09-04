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
struct option {char* member_0; char member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  const member_1; } ;
struct TYPE_3__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  LOG_PID ; 
 int /*<<< orphan*/  LOG_USER ; 
 TYPE_1__* cmds ; 
 int getopt_long (int,char**,char*,struct option const*,int /*<<< orphan*/ *) ; 
#define  no_argument 129 
 int /*<<< orphan*/  openlog (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ opterr ; 
 size_t optind ; 
 int /*<<< orphan*/  printf (char*) ; 
#define  required_argument 128 
 int run_command (TYPE_1__*,int,char**) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  usbip_help (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbip_setup_port_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_usage () ; 
 int usbip_use_debug ; 
 int usbip_use_stderr ; 
 int usbip_use_syslog ; 

int main(int argc, char *argv[])
{
	static const struct option opts[] = {
		{ "debug",    no_argument,       NULL, 'd' },
		{ "log",      no_argument,       NULL, 'l' },
		{ "tcp-port", required_argument, NULL, 't' },
		{ NULL,       0,                 NULL,  0  }
	};

	char *cmd;
	int opt;
	int i, rc = -1;

	usbip_use_stderr = 1;
	opterr = 0;
	for (;;) {
		opt = getopt_long(argc, argv, "+dlt:", opts, NULL);

		if (opt == -1)
			break;

		switch (opt) {
		case 'd':
			usbip_use_debug = 1;
			break;
		case 'l':
			usbip_use_syslog = 1;
			openlog("", LOG_PID, LOG_USER);
			break;
		case 't':
			usbip_setup_port_number(optarg);
			break;
		case '?':
			printf("usbip: invalid option\n");
			/* Terminate after printing error */
			/* FALLTHRU */
		default:
			usbip_usage();
			goto out;
		}
	}

	cmd = argv[optind];
	if (cmd) {
		for (i = 0; cmds[i].name != NULL; i++)
			if (!strcmp(cmds[i].name, cmd)) {
				argc -= optind;
				argv += optind;
				optind = 0;
				rc = run_command(&cmds[i], argc, argv);
				goto out;
			}
	}

	/* invalid command */
	usbip_help(0, NULL);
out:
	return (rc > -1 ? EXIT_SUCCESS : EXIT_FAILURE);
}