#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int phase; } ;
typedef  TYPE_1__ Barrier ;

/* Variables and functions */

int
BarrierPhase(Barrier *barrier)
{
	/*
	 * It is OK to read barrier->phase without locking, because it can't
	 * change without us (we are attached to it), and we executed a memory
	 * barrier when we either attached or participated in changing it last
	 * time.
	 */
	return barrier->phase;
}