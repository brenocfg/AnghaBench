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
typedef  int /*<<< orphan*/  os_sem_t ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 scalar_t__ ReleaseSemaphore (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int os_sem_post(os_sem_t *sem)
{
	if (!sem)
		return -1;
	return ReleaseSemaphore((HANDLE)sem, 1, NULL) ? 0 : -1;
}