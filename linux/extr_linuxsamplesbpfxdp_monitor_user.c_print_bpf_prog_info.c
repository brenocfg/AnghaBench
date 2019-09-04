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
struct TYPE_2__ {char* name; int fd; } ;

/* Variables and functions */
 int* event_fd ; 
 TYPE_1__* map_data ; 
 int map_data_count ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int prog_cnt ; 
 int* prog_fd ; 

__attribute__((used)) static void print_bpf_prog_info(void)
{
	int i;

	/* Prog info */
	printf("Loaded BPF prog have %d bpf program(s)\n", prog_cnt);
	for (i = 0; i < prog_cnt; i++) {
		printf(" - prog_fd[%d] = fd(%d)\n", i, prog_fd[i]);
	}

	/* Maps info */
	printf("Loaded BPF prog have %d map(s)\n", map_data_count);
	for (i = 0; i < map_data_count; i++) {
		char *name = map_data[i].name;
		int fd     = map_data[i].fd;

		printf(" - map_data[%d] = fd(%d) name:%s\n", i, fd, name);
	}

	/* Event info */
	printf("Searching for (max:%d) event file descriptor(s)\n", prog_cnt);
	for (i = 0; i < prog_cnt; i++) {
		if (event_fd[i] != -1)
			printf(" - event_fd[%d] = fd(%d)\n", i, event_fd[i]);
	}
}