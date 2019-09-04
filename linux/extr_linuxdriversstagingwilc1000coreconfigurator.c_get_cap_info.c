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
typedef  size_t u16 ;
typedef  enum sub_frame_type { ____Placeholder_sub_frame_type } sub_frame_type ;

/* Variables and functions */
 int BEACON ; 
 scalar_t__ BEACON_INTERVAL_LEN ; 
 size_t MAC_HDR_LEN ; 
 int PROBE_RSP ; 
 scalar_t__ TIME_STAMP_LEN ; 
 int get_sub_type (int*) ; 

__attribute__((used)) static inline u16 get_cap_info(u8 *data)
{
	u16 cap_info = 0;
	u16 index    = MAC_HDR_LEN;
	enum sub_frame_type st;

	st = get_sub_type(data);

	if (st == BEACON || st == PROBE_RSP)
		index += TIME_STAMP_LEN + BEACON_INTERVAL_LEN;

	cap_info  = data[index];
	cap_info |= (data[index + 1] << 8);

	return cap_info;
}