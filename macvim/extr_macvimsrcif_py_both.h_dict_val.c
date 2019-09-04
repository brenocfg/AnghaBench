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
typedef  int /*<<< orphan*/  hashitem_T ;
struct TYPE_3__ {int /*<<< orphan*/  di_tv; } ;
typedef  TYPE_1__ dictitem_T ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * ConvertToPyObject (int /*<<< orphan*/ *) ; 
 TYPE_1__* dict_lookup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
dict_val(hashitem_T *hi)
{
    dictitem_T	*di;

    di = dict_lookup(hi);
    return ConvertToPyObject(&di->di_tv);
}