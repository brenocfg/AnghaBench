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
struct TYPE_3__ {unsigned long winerr; int doserr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG5 ; 
 int EINVAL ; 
 int /*<<< orphan*/  LOG ; 
 TYPE_1__* doserrors ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg_internal (char*,unsigned long,...) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned long,...) ; 
 int lengthof (TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 

void
_dosmaperr(unsigned long e)
{
	int			i;

	if (e == 0)
	{
		errno = 0;
		return;
	}

	for (i = 0; i < lengthof(doserrors); i++)
	{
		if (doserrors[i].winerr == e)
		{
			int			doserr = doserrors[i].doserr;

#ifndef FRONTEND
			ereport(DEBUG5,
					(errmsg_internal("mapped win32 error code %lu to %d",
									 e, doserr)));
#elif defined(FRONTEND_DEBUG)
			fprintf(stderr, "mapped win32 error code %lu to %d", e, doserr);
#endif
			errno = doserr;
			return;
		}
	}

#ifndef FRONTEND
	ereport(LOG,
			(errmsg_internal("unrecognized win32 error code: %lu",
							 e)));
#else
	fprintf(stderr, "unrecognized win32 error code: %lu", e);
#endif

	errno = EINVAL;
	return;
}