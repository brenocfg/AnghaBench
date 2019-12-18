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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ BPF_F_NO_PREALLOC ; 
 scalar_t__ BPF_MAP_TYPE_HASH ; 
 int bpf_create_map (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ skip_unsupported_map (scalar_t__) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __create_map(uint32_t type, uint32_t size_key,
			uint32_t size_value, uint32_t max_elem,
			uint32_t extra_flags)
{
	int fd;

	fd = bpf_create_map(type, size_key, size_value, max_elem,
			    (type == BPF_MAP_TYPE_HASH ?
			     BPF_F_NO_PREALLOC : 0) | extra_flags);
	if (fd < 0) {
		if (skip_unsupported_map(type))
			return -1;
		printf("Failed to create hash map '%s'!\n", strerror(errno));
	}

	return fd;
}