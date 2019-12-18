#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* tab; } ;
typedef  TYPE_1__ TabPageObject ;
struct TYPE_8__ {int /*<<< orphan*/  tp_curwin; int /*<<< orphan*/  tp_vars; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * NEW_DICTIONARY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ObjectDir (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyLong_FromLong (long) ; 
 int /*<<< orphan*/  TabPageAttrs ; 
 int /*<<< orphan*/ * WinListNew (TYPE_1__*) ; 
 int /*<<< orphan*/ * WindowNew (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* curtab ; 
 int /*<<< orphan*/  curwin ; 
 scalar_t__ get_tab_number (TYPE_2__*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static PyObject *
TabPageAttr(TabPageObject *self, char *name)
{
    if (strcmp(name, "windows") == 0)
	return WinListNew(self);
    else if (strcmp(name, "number") == 0)
	return PyLong_FromLong((long) get_tab_number(self->tab));
    else if (strcmp(name, "vars") == 0)
	return NEW_DICTIONARY(self->tab->tp_vars);
    else if (strcmp(name, "window") == 0)
    {
	/* For current tab window.c does not bother to set or update tp_curwin
	 */
	if (self->tab == curtab)
	    return WindowNew(curwin, curtab);
	else
	    return WindowNew(self->tab->tp_curwin, self->tab);
    }
    else if (strcmp(name, "__members__") == 0)
	return ObjectDir(NULL, TabPageAttrs);
    return NULL;
}