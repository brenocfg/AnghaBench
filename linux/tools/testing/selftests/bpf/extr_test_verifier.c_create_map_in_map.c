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
 int /*<<< orphan*/  BPF_MAP_TYPE_ARRAY ; 
 int /*<<< orphan*/  BPF_MAP_TYPE_ARRAY_OF_MAPS ; 
 int bpf_create_map (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int bpf_create_map_in_map (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ skip_unsupported_map (int /*<<< orphan*/ ) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_map_in_map(void)
{
	int inner_map_fd, outer_map_fd;

	inner_map_fd = bpf_create_map(BPF_MAP_TYPE_ARRAY, sizeof(int),
				      sizeof(int), 1, 0);
	if (inner_map_fd < 0) {
		if (skip_unsupported_map(BPF_MAP_TYPE_ARRAY))
			return -1;
		printf("Failed to create array '%s'!\n", strerror(errno));
		return inner_map_fd;
	}

	outer_map_fd = bpf_create_map_in_map(BPF_MAP_TYPE_ARRAY_OF_MAPS, NULL,
					     sizeof(int), inner_map_fd, 1, 0);
	if (outer_map_fd < 0) {
		if (skip_unsupported_map(BPF_MAP_TYPE_ARRAY_OF_MAPS))
			return -1;
		printf("Failed to create array of maps '%s'!\n",
		       strerror(errno));
	}

	close(inner_map_fd);

	return outer_map_fd;
}