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
struct TYPE_4__ {int /*<<< orphan*/  error; int /*<<< orphan*/  mmgr; } ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  int /*<<< orphan*/  HPDF_Real ;
typedef  int /*<<< orphan*/  HPDF_REAL ;
typedef  TYPE_1__* HPDF_Array ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_Array_Add (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Error_GetCode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_Real_New (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HPDF_STATUS
HPDF_Array_AddReal  (HPDF_Array  array,
                     HPDF_REAL   value)
{
    HPDF_Real r = HPDF_Real_New (array->mmgr, value);

    HPDF_PTRACE((" HPDF_Array_AddReal\n"));

    if (!r)
        return HPDF_Error_GetCode (array->error);
    else
        return HPDF_Array_Add (array, r);
}