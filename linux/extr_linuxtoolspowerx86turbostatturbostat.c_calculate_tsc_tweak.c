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
 int base_hz ; 
 int tsc_hz ; 
 int tsc_tweak ; 

__attribute__((used)) static void
calculate_tsc_tweak()
{
	tsc_tweak = base_hz / tsc_hz;
}