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
struct TYPE_3__ {scalar_t__ win; } ;
typedef  TYPE_1__ WindowObject ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 scalar_t__ INVALID_WINDOW_VALUE ; 
 int /*<<< orphan*/ * PyString_FromFormat (char*,...) ; 
 int /*<<< orphan*/  firstwin ; 
 int get_win_number (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
WindowRepr(WindowObject *self)
{
    if (self->win == INVALID_WINDOW_VALUE)
	return PyString_FromFormat("<window object (deleted) at %p>", (self));
    else
    {
	int	w = get_win_number(self->win, firstwin);

	if (w == 0)
	    return PyString_FromFormat("<window object (unknown) at %p>",
								      (self));
	else
	    return PyString_FromFormat("<window %d>", w - 1);
    }
}