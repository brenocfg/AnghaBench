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
typedef  int /*<<< orphan*/  PGSemaphore ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WAIT_TIMEOUT ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 

bool
PGSemaphoreTryLock(PGSemaphore sema)
{
	DWORD		ret;

	ret = WaitForSingleObject(sema, 0);

	if (ret == WAIT_OBJECT_0)
	{
		/* We got it! */
		return true;
	}
	else if (ret == WAIT_TIMEOUT)
	{
		/* Can't get it */
		errno = EAGAIN;
		return false;
	}

	/* Otherwise we are in trouble */
	ereport(FATAL,
			(errmsg("could not try-lock semaphore: error code %lu",
					GetLastError())));

	/* keep compiler quiet */
	return false;
}