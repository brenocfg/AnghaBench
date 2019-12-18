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
struct isst_if_msr_cmds {int cmd_count; TYPE_1__* msr_cmd; } ;
struct TYPE_2__ {unsigned int logical_cpu; unsigned int msr; int read_write; unsigned long long data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISST_IF_MSR_COMMAND ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  debug_printf (char*,unsigned int,unsigned int,int,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,int) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct isst_if_msr_cmds*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outf ; 
 int /*<<< orphan*/  perror (char*) ; 

int isst_send_msr_command(unsigned int cpu, unsigned int msr, int write,
			  unsigned long long *req_resp)
{
	struct isst_if_msr_cmds msr_cmds;
	const char *pathname = "/dev/isst_interface";
	int fd;

	fd = open(pathname, O_RDWR);
	if (fd < 0)
		err(-1, "%s open failed", pathname);

	msr_cmds.cmd_count = 1;
	msr_cmds.msr_cmd[0].logical_cpu = cpu;
	msr_cmds.msr_cmd[0].msr = msr;
	msr_cmds.msr_cmd[0].read_write = write;
	if (write)
		msr_cmds.msr_cmd[0].data = *req_resp;

	if (ioctl(fd, ISST_IF_MSR_COMMAND, &msr_cmds) == -1) {
		perror("ISST_IF_MSR_COMMAD");
		fprintf(outf, "Error: msr_cmd cpu:%d msr:%x read_write:%d\n",
			cpu, msr, write);
	} else {
		if (!write)
			*req_resp = msr_cmds.msr_cmd[0].data;

		debug_printf(
			"msr_cmd response: cpu:%d msr:%x rd_write:%x resp:%llx %llx\n",
			cpu, msr, write, *req_resp, msr_cmds.msr_cmd[0].data);
	}

	close(fd);

	return 0;
}