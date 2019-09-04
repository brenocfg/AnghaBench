#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * ob_type; } ;
struct TYPE_5__ {int /*<<< orphan*/ * setitem; int /*<<< orphan*/ * getitem; int /*<<< orphan*/  copyswap; } ;
typedef  int /*<<< orphan*/  PyArray_SetItemFunc ;
typedef  int /*<<< orphan*/  PyArray_GetItemFunc ;
typedef  int /*<<< orphan*/  PyArray_Descr ;

/* Variables and functions */
 int /*<<< orphan*/  PyArrayDescr_Type ; 
 int /*<<< orphan*/ * PyArray_DescrFromType (int) ; 
 int /*<<< orphan*/  PyArray_InitArrFuncs (TYPE_1__*) ; 
 int PyArray_RegisterDataType (TYPE_2__*) ; 
 TYPE_2__ _PyFloatInt_Dtype ; 
 TYPE_1__ _PyFloatInt_Funcs ; 
 int /*<<< orphan*/  twoint_copyswap ; 
 scalar_t__ twoint_getitem ; 
 scalar_t__ twoint_setitem ; 

__attribute__((used)) static PyArray_Descr * _register_dtype(void)
{
    int userval;
    PyArray_InitArrFuncs(&_PyFloatInt_Funcs); 
    /* Add copyswap,
       nonzero, getitem, setitem*/
    _PyFloatInt_Funcs.copyswap = twoint_copyswap;
    _PyFloatInt_Funcs.getitem = (PyArray_GetItemFunc *)twoint_getitem;
    _PyFloatInt_Funcs.setitem = (PyArray_SetItemFunc *)twoint_setitem; 
    _PyFloatInt_Dtype.ob_type = &PyArrayDescr_Type;

    userval = PyArray_RegisterDataType(&_PyFloatInt_Dtype);
    return PyArray_DescrFromType(userval);
}