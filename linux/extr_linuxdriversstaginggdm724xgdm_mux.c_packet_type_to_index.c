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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 int TTY_MAX_COUNT ; 
 scalar_t__* packet_type ; 

__attribute__((used)) static int packet_type_to_index(u16 packetType)
{
	int i;

	for (i = 0; i < TTY_MAX_COUNT; i++) {
		if (packet_type[i] == packetType)
			return i;
	}

	return -1;
}