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
typedef  int /*<<< orphan*/  LONG ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 scalar_t__ CreateSemaphore (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int os_sem_init(os_sem_t **sem, int value)
{
	HANDLE handle = CreateSemaphore(NULL, (LONG)value, 0x7FFFFFFF, NULL);
	if (!handle)
		return -1;

	*sem = (os_sem_t *)handle;
	return 0;
}