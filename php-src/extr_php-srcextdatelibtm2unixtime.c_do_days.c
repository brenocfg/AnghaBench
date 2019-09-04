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
typedef  int timelib_ull ;
typedef  int timelib_sll ;

/* Variables and functions */
 int SECS_PER_DAY ; 

__attribute__((used)) static timelib_sll do_days(timelib_ull day)
{
	return ((day - 1) * SECS_PER_DAY);
}