#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int closed; int /*<<< orphan*/ * mcxt; int /*<<< orphan*/  portalname; } ;
struct TYPE_7__ {TYPE_1__* ob_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* tp_free ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ PyObject ;
typedef  int /*<<< orphan*/  Portal ;
typedef  TYPE_3__ PLyCursorObject ;

/* Variables and functions */
 int /*<<< orphan*/  GetPortalByName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ *) ; 
 scalar_t__ PortalIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_cursor_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnpinPortal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void
PLy_cursor_dealloc(PyObject *arg)
{
	PLyCursorObject *cursor;
	Portal		portal;

	cursor = (PLyCursorObject *) arg;

	if (!cursor->closed)
	{
		portal = GetPortalByName(cursor->portalname);

		if (PortalIsValid(portal))
		{
			UnpinPortal(portal);
			SPI_cursor_close(portal);
		}
		cursor->closed = true;
	}
	if (cursor->mcxt)
	{
		MemoryContextDelete(cursor->mcxt);
		cursor->mcxt = NULL;
	}
	arg->ob_type->tp_free(arg);
}