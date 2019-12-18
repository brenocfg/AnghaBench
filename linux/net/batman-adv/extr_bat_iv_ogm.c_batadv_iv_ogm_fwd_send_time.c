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
 int BATADV_JITTER ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int prandom_u32 () ; 

__attribute__((used)) static unsigned long batadv_iv_ogm_fwd_send_time(void)
{
	return jiffies + msecs_to_jiffies(prandom_u32() % (BATADV_JITTER / 2));
}