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
union semun {int val; } ;
typedef  int /*<<< orphan*/  IpcSemaphoreId ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  SETVAL ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*,int) ; 
 int /*<<< orphan*/  errmsg_internal (char*,int /*<<< orphan*/ ,int,int) ; 
 int errno ; 
 scalar_t__ semctl (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,union semun) ; 

__attribute__((used)) static void
IpcSemaphoreInitialize(IpcSemaphoreId semId, int semNum, int value)
{
	union semun semun;

	semun.val = value;
	if (semctl(semId, semNum, SETVAL, semun) < 0)
	{
		int			saved_errno = errno;

		ereport(FATAL,
				(errmsg_internal("semctl(%d, %d, SETVAL, %d) failed: %m",
								 semId, semNum, value),
				 (saved_errno == ERANGE) ?
				 errhint("You possibly need to raise your kernel's SEMVMX value to be at least "
						 "%d.  Look into the PostgreSQL documentation for details.",
						 value) : 0));
	}
}