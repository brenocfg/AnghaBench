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

/* Variables and functions */
 char* bpf_log_buf ; 
 int /*<<< orphan*/  get_data (int /*<<< orphan*/ ) ; 
 scalar_t__ load_bpf_file (char*) ; 
 int /*<<< orphan*/ * map_fd ; 
 int /*<<< orphan*/  print_hist () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

int main(int argc, char **argv)
{
	char filename[256];

	snprintf(filename, sizeof(filename), "%s_kern.o", argv[0]);

	if (load_bpf_file(filename)) {
		printf("%s", bpf_log_buf);
		return 1;
	}

	while (1) {
		get_data(map_fd[1]);
		print_hist();
		sleep(5);
	}

	return 0;
}