#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dv_refcount; } ;
typedef  TYPE_1__ dict_T ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 TYPE_1__* dict_alloc () ; 

__attribute__((used)) static dict_T *
py_dict_alloc(void)
{
    dict_T	*ret;

    if (!(ret = dict_alloc()))
    {
	PyErr_NoMemory();
	return NULL;
    }
    ++ret->dv_refcount;

    return ret;
}