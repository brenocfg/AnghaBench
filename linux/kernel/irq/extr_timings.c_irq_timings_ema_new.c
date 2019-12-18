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
typedef  int u64 ;
typedef  int s64 ;

/* Variables and functions */
 int EMA_ALPHA_SHIFT ; 
 int EMA_ALPHA_VAL ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u64 irq_timings_ema_new(u64 value, u64 ema_old)
{
	s64 diff;

	if (unlikely(!ema_old))
		return value;

	diff = (value - ema_old) * EMA_ALPHA_VAL;
	/*
	 * We can use a s64 type variable to be added with the u64
	 * ema_old variable as this one will never have its topmost
	 * bit set, it will be always smaller than 2^63 nanosec
	 * interrupt interval (292 years).
	 */
	return ema_old + (diff >> EMA_ALPHA_SHIFT);
}