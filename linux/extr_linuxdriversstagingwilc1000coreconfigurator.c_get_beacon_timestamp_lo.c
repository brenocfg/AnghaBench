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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int MAC_HDR_LEN ; 

__attribute__((used)) static inline u32 get_beacon_timestamp_lo(u8 *data)
{
	u32 time_stamp = 0;
	u32 index    = MAC_HDR_LEN;

	time_stamp |= data[index++];
	time_stamp |= (data[index++] << 8);
	time_stamp |= (data[index++] << 16);
	time_stamp |= (data[index]   << 24);

	return time_stamp;
}