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
struct k_itimer {scalar_t__ it_overrun_last; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int INT_MAX ; 

__attribute__((used)) static inline int timer_overrun_to_int(struct k_itimer *timr, int baseval)
{
	s64 sum = timr->it_overrun_last + (s64)baseval;

	return sum > (s64)INT_MAX ? INT_MAX : (int)sum;
}