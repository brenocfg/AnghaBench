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
struct TYPE_3__ {int is_internal; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ObjectAccessPostCreate ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OAT_POST_CREATE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  object_access_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ; 

void
RunObjectPostCreateHook(Oid classId, Oid objectId, int subId,
						bool is_internal)
{
	ObjectAccessPostCreate pc_arg;

	/* caller should check, but just in case... */
	Assert(object_access_hook != NULL);

	memset(&pc_arg, 0, sizeof(ObjectAccessPostCreate));
	pc_arg.is_internal = is_internal;

	(*object_access_hook) (OAT_POST_CREATE,
						   classId, objectId, subId,
						   (void *) &pc_arg);
}