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
typedef  scalar_t__ IpcSemaphoreKey ;
typedef  int IpcSemaphoreId ;

/* Variables and functions */
 int EACCES ; 
 int EEXIST ; 
 int EIDRM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  FATAL ; 
 int IPCProtection ; 
 int IPC_CREAT ; 
 int IPC_EXCL ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,unsigned long,int,int) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int errno ; 
 int semget (scalar_t__,int,int) ; 

__attribute__((used)) static IpcSemaphoreId
InternalIpcSemaphoreCreate(IpcSemaphoreKey semKey, int numSems)
{
	int			semId;

	semId = semget(semKey, numSems, IPC_CREAT | IPC_EXCL | IPCProtection);

	if (semId < 0)
	{
		int			saved_errno = errno;

		/*
		 * Fail quietly if error indicates a collision with existing set. One
		 * would expect EEXIST, given that we said IPC_EXCL, but perhaps we
		 * could get a permission violation instead?  Also, EIDRM might occur
		 * if an old set is slated for destruction but not gone yet.
		 */
		if (saved_errno == EEXIST || saved_errno == EACCES
#ifdef EIDRM
			|| saved_errno == EIDRM
#endif
			)
			return -1;

		/*
		 * Else complain and abort
		 */
		ereport(FATAL,
				(errmsg("could not create semaphores: %m"),
				 errdetail("Failed system call was semget(%lu, %d, 0%o).",
						   (unsigned long) semKey, numSems,
						   IPC_CREAT | IPC_EXCL | IPCProtection),
				 (saved_errno == ENOSPC) ?
				 errhint("This error does *not* mean that you have run out of disk space.  "
						 "It occurs when either the system limit for the maximum number of "
						 "semaphore sets (SEMMNI), or the system wide maximum number of "
						 "semaphores (SEMMNS), would be exceeded.  You need to raise the "
						 "respective kernel parameter.  Alternatively, reduce PostgreSQL's "
						 "consumption of semaphores by reducing its max_connections parameter.\n"
						 "The PostgreSQL documentation contains more information about "
						 "configuring your system for PostgreSQL.") : 0));
	}

	return semId;
}