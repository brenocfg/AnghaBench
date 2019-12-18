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
struct TYPE_3__ {int /*<<< orphan*/ * AH; } ;
typedef  TYPE_1__ ParallelSlot ;
typedef  int /*<<< orphan*/  ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_info_lock ; 

__attribute__((used)) static void
set_cancel_slot_archive(ParallelSlot *slot, ArchiveHandle *AH)
{
#ifdef WIN32
	EnterCriticalSection(&signal_info_lock);
#endif

	slot->AH = AH;

#ifdef WIN32
	LeaveCriticalSection(&signal_info_lock);
#endif
}