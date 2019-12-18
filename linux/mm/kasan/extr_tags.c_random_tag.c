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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;

/* Variables and functions */
 int KASAN_TAG_MAX ; 
 int /*<<< orphan*/  prng_state ; 
 int this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,int) ; 

u8 random_tag(void)
{
	u32 state = this_cpu_read(prng_state);

	state = 1664525 * state + 1013904223;
	this_cpu_write(prng_state, state);

	return (u8)(state % (KASAN_TAG_MAX + 1));
}