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
typedef  int /*<<< orphan*/  win_T ;
struct TYPE_3__ {int /*<<< orphan*/  tabObject; } ;
typedef  TYPE_1__ WinListObject ;
typedef  int PyInt ;

/* Variables and functions */
 int /*<<< orphan*/ * W_NEXT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_firstwin (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyInt
WinListLength(WinListObject *self)
{
    win_T	*w;
    PyInt	n = 0;

    if (!(w = get_firstwin(self->tabObject)))
	return -1;

    while (w != NULL)
    {
	++n;
	w = W_NEXT(w);
    }

    return n;
}