#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* shared; } ;
struct TYPE_9__ {TYPE_1__* shared; } ;
struct TYPE_8__ {int /*<<< orphan*/  nextOffset; int /*<<< orphan*/  nextMXact; } ;
struct TYPE_7__ {int latest_page_number; } ;
struct TYPE_6__ {int latest_page_number; } ;
typedef  int /*<<< orphan*/  MultiXactOffset ;
typedef  int /*<<< orphan*/  MultiXactId ;

/* Variables and functions */
 int MXOffsetToMemberPage (int /*<<< orphan*/ ) ; 
 int MultiXactIdToOffsetPage (int /*<<< orphan*/ ) ; 
 TYPE_5__* MultiXactMemberCtl ; 
 TYPE_4__* MultiXactOffsetCtl ; 
 TYPE_3__* MultiXactState ; 

void
StartupMultiXact(void)
{
	MultiXactId multi = MultiXactState->nextMXact;
	MultiXactOffset offset = MultiXactState->nextOffset;
	int			pageno;

	/*
	 * Initialize offset's idea of the latest page number.
	 */
	pageno = MultiXactIdToOffsetPage(multi);
	MultiXactOffsetCtl->shared->latest_page_number = pageno;

	/*
	 * Initialize member's idea of the latest page number.
	 */
	pageno = MXOffsetToMemberPage(offset);
	MultiXactMemberCtl->shared->latest_page_number = pageno;
}