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
typedef  int u32 ;

/* Variables and functions */
 int TCP_INIT_CWND ; 
 int max (int,unsigned int) ; 

u32 tcp_default_init_rwnd(u32 mss)
{
	/* Initial receive window should be twice of TCP_INIT_CWND to
	 * enable proper sending of new unsent data during fast recovery
	 * (RFC 3517, Section 4, NextSeg() rule (2)). Further place a
	 * limit when mss is larger than 1460.
	 */
	u32 init_rwnd = TCP_INIT_CWND * 2;

	if (mss > 1460)
		init_rwnd = max((1460 * init_rwnd) / mss, 2U);
	return init_rwnd;
}