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
struct TYPE_3__ {int dropflags; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ObjectAccessDrop ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OAT_DROP ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  object_access_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ; 

void
RunObjectDropHook(Oid classId, Oid objectId, int subId,
				  int dropflags)
{
	ObjectAccessDrop drop_arg;

	/* caller should check, but just in case... */
	Assert(object_access_hook != NULL);

	memset(&drop_arg, 0, sizeof(ObjectAccessDrop));
	drop_arg.dropflags = dropflags;

	(*object_access_hook) (OAT_DROP,
						   classId, objectId, subId,
						   (void *) &drop_arg);
}