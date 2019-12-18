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

/* Variables and functions */
 scalar_t__ INVALID_WINDOW_VALUE ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  PyErr_SET_VIM (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
CheckWindow(WindowObject *self)
{
    if (self->win == INVALID_WINDOW_VALUE)
    {
	PyErr_SET_VIM(N_("attempt to refer to deleted window"));
	return -1;
    }

    return 0;
}