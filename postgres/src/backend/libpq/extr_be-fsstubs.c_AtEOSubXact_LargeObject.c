#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ subid; } ;
typedef  scalar_t__ SubTransactionId ;
typedef  TYPE_1__ LargeObjectDesc ;

/* Variables and functions */
 TYPE_1__** cookies ; 
 int cookies_size ; 
 int /*<<< orphan*/  deleteLOfd (int) ; 
 int /*<<< orphan*/ * fscxt ; 
 int /*<<< orphan*/  inv_close (TYPE_1__*) ; 

void
AtEOSubXact_LargeObject(bool isCommit, SubTransactionId mySubid,
						SubTransactionId parentSubid)
{
	int			i;

	if (fscxt == NULL)			/* no LO operations in this xact */
		return;

	for (i = 0; i < cookies_size; i++)
	{
		LargeObjectDesc *lo = cookies[i];

		if (lo != NULL && lo->subid == mySubid)
		{
			if (isCommit)
				lo->subid = parentSubid;
			else
			{
				/*
				 * Make sure we do not call inv_close twice if it errors out
				 * for some reason.  Better a leak than a crash.
				 */
				deleteLOfd(i);
				inv_close(lo);
			}
		}
	}
}