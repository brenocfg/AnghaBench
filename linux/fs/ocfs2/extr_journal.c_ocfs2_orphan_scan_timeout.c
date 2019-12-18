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
typedef  int /*<<< orphan*/  time ;

/* Variables and functions */
 unsigned long ORPHAN_SCAN_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  get_random_bytes (unsigned long*,int) ; 
 unsigned long msecs_to_jiffies (unsigned long) ; 

__attribute__((used)) static inline unsigned long ocfs2_orphan_scan_timeout(void)
{
	unsigned long time;

	get_random_bytes(&time, sizeof(time));
	time = ORPHAN_SCAN_SCHEDULE_TIMEOUT + (time % 5000);
	return msecs_to_jiffies(time);
}