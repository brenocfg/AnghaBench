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
struct ad7280_state {int readback_delay_us; } ;

/* Variables and functions */
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void ad7280_delay(struct ad7280_state *st)
{
	if (st->readback_delay_us < 50)
		udelay(st->readback_delay_us);
	else
		usleep_range(250, 500);
}