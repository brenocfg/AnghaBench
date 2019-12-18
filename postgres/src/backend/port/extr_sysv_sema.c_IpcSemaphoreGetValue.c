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
union semun {scalar_t__ val; } ;
typedef  int /*<<< orphan*/  IpcSemaphoreId ;

/* Variables and functions */
 int /*<<< orphan*/  GETVAL ; 
 int semctl (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,union semun) ; 

__attribute__((used)) static int
IpcSemaphoreGetValue(IpcSemaphoreId semId, int semNum)
{
	union semun dummy;			/* for Solaris */

	dummy.val = 0;				/* unused */

	return semctl(semId, semNum, GETVAL, dummy);
}