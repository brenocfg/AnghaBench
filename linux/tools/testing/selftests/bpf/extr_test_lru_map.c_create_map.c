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
 int bpf_create_map (int,int,int,unsigned int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static int create_map(int map_type, int map_flags, unsigned int size)
{
	int map_fd;

	map_fd = bpf_create_map(map_type, sizeof(unsigned long long),
				sizeof(unsigned long long), size, map_flags);

	if (map_fd == -1)
		perror("bpf_create_map");

	return map_fd;
}