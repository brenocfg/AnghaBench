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
typedef  int /*<<< orphan*/  msg ;
struct TYPE_9__ {int backend; int /*<<< orphan*/  node; } ;
struct TYPE_7__ {int backend_hi; int backend_lo; int /*<<< orphan*/  rnode; int /*<<< orphan*/  id; } ;
struct TYPE_8__ {TYPE_1__ sm; } ;
typedef  TYPE_2__ SharedInvalidationMessage ;
typedef  TYPE_3__ RelFileNodeBackend ;

/* Variables and functions */
 int /*<<< orphan*/  SHAREDINVALSMGR_ID ; 
 int /*<<< orphan*/  SendSharedInvalidMessages (TYPE_2__*,int) ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_DEFINED (TYPE_2__*,int) ; 

void
CacheInvalidateSmgr(RelFileNodeBackend rnode)
{
	SharedInvalidationMessage msg;

	msg.sm.id = SHAREDINVALSMGR_ID;
	msg.sm.backend_hi = rnode.backend >> 16;
	msg.sm.backend_lo = rnode.backend & 0xffff;
	msg.sm.rnode = rnode.node;
	/* check AddCatcacheInvalidationMessage() for an explanation */
	VALGRIND_MAKE_MEM_DEFINED(&msg, sizeof(msg));

	SendSharedInvalidMessages(&msg, 1);
}