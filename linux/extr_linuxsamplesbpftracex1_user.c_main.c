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
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* bpf_log_buf ; 
 scalar_t__ load_bpf_file (char*) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  read_trace_pipe () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

int main(int ac, char **argv)
{
	FILE *f;
	char filename[256];

	snprintf(filename, sizeof(filename), "%s_kern.o", argv[0]);

	if (load_bpf_file(filename)) {
		printf("%s", bpf_log_buf);
		return 1;
	}

	f = popen("taskset 1 ping -c5 localhost", "r");
	(void) f;

	read_trace_pipe();

	return 0;
}