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
 int bpf_set_link_xdp_fd (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

__attribute__((used)) static int do_detach(int idx, const char *name)
{
	int err;

	err = bpf_set_link_xdp_fd(idx, -1, 0);
	if (err < 0)
		printf("ERROR: failed to detach program from %s\n", name);

	/* TODO: Remember to cleanup map, when adding use of shared map
	 *  bpf_map_delete_elem((map_fd, &idx);
	 */
	return err;
}