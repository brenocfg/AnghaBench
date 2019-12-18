#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  msg ;
struct TYPE_5__ {int /*<<< orphan*/  dbId; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_1__ rm; } ;
typedef  TYPE_2__ SharedInvalidationMessage ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  SHAREDINVALRELMAP_ID ; 
 int /*<<< orphan*/  SendSharedInvalidMessages (TYPE_2__*,int) ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_DEFINED (TYPE_2__*,int) ; 

void
CacheInvalidateRelmap(Oid databaseId)
{
	SharedInvalidationMessage msg;

	msg.rm.id = SHAREDINVALRELMAP_ID;
	msg.rm.dbId = databaseId;
	/* check AddCatcacheInvalidationMessage() for an explanation */
	VALGRIND_MAKE_MEM_DEFINED(&msg, sizeof(msg));

	SendSharedInvalidMessages(&msg, 1);
}