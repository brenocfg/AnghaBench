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
typedef  int u64 ;

/* Variables and functions */
 int BA_SETUP_MAX_PACKET_THRESHOLD ; 
 int BA_SETUP_PACKET_OFFSET ; 
 int ktime_get_ns () ; 

__attribute__((used)) static u8 mwifiex_get_random_ba_threshold(void)
{
	u64 ns;
	/* setup ba_packet_threshold here random number between
	 * [BA_SETUP_PACKET_OFFSET,
	 * BA_SETUP_PACKET_OFFSET+BA_SETUP_MAX_PACKET_THRESHOLD-1]
	 */
	ns = ktime_get_ns();
	ns += (ns >> 32) + (ns >> 16);

	return ((u8)ns % BA_SETUP_MAX_PACKET_THRESHOLD) + BA_SETUP_PACKET_OFFSET;
}