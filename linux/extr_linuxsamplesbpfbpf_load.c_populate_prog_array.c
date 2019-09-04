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

/* Variables and functions */
 int /*<<< orphan*/  BPF_ANY ; 
 int atoi (char const*) ; 
 int bpf_map_update_elem (int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  prog_array_fd ; 

__attribute__((used)) static int populate_prog_array(const char *event, int prog_fd)
{
	int ind = atoi(event), err;

	err = bpf_map_update_elem(prog_array_fd, &ind, &prog_fd, BPF_ANY);
	if (err < 0) {
		printf("failed to store prog_fd in prog_array\n");
		return -1;
	}
	return 0;
}