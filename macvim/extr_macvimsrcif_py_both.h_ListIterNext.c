#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* lw_item; } ;
struct TYPE_7__ {TYPE_2__ lw; } ;
typedef  TYPE_3__ listiterinfo_T ;
struct TYPE_5__ {struct TYPE_5__* li_next; int /*<<< orphan*/  li_tv; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * ConvertToPyObject (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
ListIterNext(listiterinfo_T **lii)
{
    PyObject	*ret;

    if (!((*lii)->lw.lw_item))
	return NULL;

    if (!(ret = ConvertToPyObject(&((*lii)->lw.lw_item->li_tv))))
	return NULL;

    (*lii)->lw.lw_item = (*lii)->lw.lw_item->li_next;

    return ret;
}