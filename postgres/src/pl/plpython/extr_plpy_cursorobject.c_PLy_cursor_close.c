#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int closed; int /*<<< orphan*/  portalname; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  Portal ;
typedef  TYPE_1__ PLyCursorObject ;

/* Variables and functions */
 int /*<<< orphan*/  GetPortalByName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLy_exception_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PortalIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  SPI_cursor_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnpinPortal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
PLy_cursor_close(PyObject *self, PyObject *unused)
{
	PLyCursorObject *cursor = (PLyCursorObject *) self;

	if (!cursor->closed)
	{
		Portal		portal = GetPortalByName(cursor->portalname);

		if (!PortalIsValid(portal))
		{
			PLy_exception_set(PyExc_ValueError,
							  "closing a cursor in an aborted subtransaction");
			return NULL;
		}

		UnpinPortal(portal);
		SPI_cursor_close(portal);
		cursor->closed = true;
	}

	Py_RETURN_NONE;
}