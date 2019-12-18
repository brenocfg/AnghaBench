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
typedef  int /*<<< orphan*/  sem_t ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ sem_init (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
PosixSemaphoreCreate(sem_t *sem)
{
	if (sem_init(sem, 1, 1) < 0)
		elog(FATAL, "sem_init failed: %m");
}