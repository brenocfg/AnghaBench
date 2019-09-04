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
 int ARRAY_SIZE (int**) ; 
 int EINVAL ; 
 int** base_to_fuse_addr_mappings ; 

__attribute__((used)) static int vf610_get_fuse_address(int base_addr_offset)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(base_to_fuse_addr_mappings); i++) {
		if (base_to_fuse_addr_mappings[i][0] == base_addr_offset)
			return base_to_fuse_addr_mappings[i][1];
	}

	return -EINVAL;
}