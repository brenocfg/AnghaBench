#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  msg ;
typedef  scalar_t__ int8 ;
struct TYPE_9__ {int /*<<< orphan*/  cclist; } ;
struct TYPE_7__ {int /*<<< orphan*/  hashValue; int /*<<< orphan*/  dbId; scalar_t__ id; } ;
struct TYPE_8__ {TYPE_1__ cc; } ;
typedef  TYPE_2__ SharedInvalidationMessage ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_3__ InvalidationListHeader ;

/* Variables and functions */
 int /*<<< orphan*/  AddInvalidationMessage (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int CHAR_MAX ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_DEFINED (TYPE_2__*,int) ; 

__attribute__((used)) static void
AddCatcacheInvalidationMessage(InvalidationListHeader *hdr,
							   int id, uint32 hashValue, Oid dbId)
{
	SharedInvalidationMessage msg;

	Assert(id < CHAR_MAX);
	msg.cc.id = (int8) id;
	msg.cc.dbId = dbId;
	msg.cc.hashValue = hashValue;

	/*
	 * Define padding bytes in SharedInvalidationMessage structs to be
	 * defined. Otherwise the sinvaladt.c ringbuffer, which is accessed by
	 * multiple processes, will cause spurious valgrind warnings about
	 * undefined memory being used. That's because valgrind remembers the
	 * undefined bytes from the last local process's store, not realizing that
	 * another process has written since, filling the previously uninitialized
	 * bytes
	 */
	VALGRIND_MAKE_MEM_DEFINED(&msg, sizeof(msg));

	AddInvalidationMessage(&hdr->cclist, &msg);
}