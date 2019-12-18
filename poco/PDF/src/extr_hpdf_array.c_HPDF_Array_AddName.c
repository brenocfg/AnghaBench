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
typedef  int /*<<< orphan*/  HPDF_Name ;
typedef  TYPE_1__* HPDF_Array ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_Array_Add (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Error_GetCode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Name_New (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

HPDF_STATUS
HPDF_Array_AddName  (HPDF_Array       array,
                     const char  *value)
{
    HPDF_Name n = HPDF_Name_New (array->mmgr, value);

    HPDF_PTRACE((" HPDF_Array_AddName\n"));

    if (!n)
        return HPDF_Error_GetCode (array->error);
    else
        return HPDF_Array_Add (array, n);
}