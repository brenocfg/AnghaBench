#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  slock_t ;
struct TYPE_5__ {int delays; } ;
typedef  TYPE_1__ SpinDelayStatus ;

/* Variables and functions */
 scalar_t__ TAS_SPIN (int /*<<< orphan*/  volatile*) ; 
 int /*<<< orphan*/  finish_spin_delay (TYPE_1__*) ; 
 int /*<<< orphan*/  init_spin_delay (TYPE_1__*,char const*,int,char const*) ; 
 int /*<<< orphan*/  perform_spin_delay (TYPE_1__*) ; 

int
s_lock(volatile slock_t *lock, const char *file, int line, const char *func)
{
	SpinDelayStatus delayStatus;

	init_spin_delay(&delayStatus, file, line, func);

	while (TAS_SPIN(lock))
	{
		perform_spin_delay(&delayStatus);
	}

	finish_spin_delay(&delayStatus);

	return delayStatus.delays;
}