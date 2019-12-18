#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sa ;
struct TYPE_7__ {int is_set; int is_shared; scalar_t__ owner_pid; int /*<<< orphan*/ * event; } ;
struct TYPE_6__ {int nLength; int /*<<< orphan*/  bInheritHandle; } ;
typedef  TYPE_1__ SECURITY_ATTRIBUTES ;
typedef  TYPE_2__ Latch ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateEvent (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
InitSharedLatch(Latch *latch)
{
#ifdef WIN32
	SECURITY_ATTRIBUTES sa;

	/*
	 * Set up security attributes to specify that the events are inherited.
	 */
	ZeroMemory(&sa, sizeof(sa));
	sa.nLength = sizeof(sa);
	sa.bInheritHandle = TRUE;

	latch->event = CreateEvent(&sa, TRUE, FALSE, NULL);
	if (latch->event == NULL)
		elog(ERROR, "CreateEvent failed: error code %lu", GetLastError());
#endif

	latch->is_set = false;
	latch->owner_pid = 0;
	latch->is_shared = true;
}