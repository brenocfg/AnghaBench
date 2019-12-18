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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__* volume_map ; 

__attribute__((used)) static inline unsigned int hsw_ipc_to_mixer(u32 value)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(volume_map); i++) {
		if (volume_map[i] >= value)
			return i;
	}

	return i - 1;
}