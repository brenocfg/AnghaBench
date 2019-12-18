#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  error; int /*<<< orphan*/  mmgr; } ;
struct TYPE_9__ {int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_1__* HPDF_Number ;
typedef  TYPE_2__* HPDF_Dict ;
typedef  int /*<<< orphan*/  HPDF_Array ;

/* Variables and functions */
 int /*<<< orphan*/  GetPageCount (TYPE_2__*) ; 
 int /*<<< orphan*/  HPDF_Dict_Add (TYPE_2__*,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  HPDF_Dict_GetItem (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Error_GetCode (int /*<<< orphan*/ ) ; 
 TYPE_1__* HPDF_Number_New (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_OCLASS_ARRAY ; 
 int /*<<< orphan*/  HPDF_OCLASS_NUMBER ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PAGES_MISSING_KIDS_ENTRY ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HPDF_STATUS
Pages_BeforeWrite  (HPDF_Dict    obj)
{
    HPDF_Array kids = (HPDF_Array )HPDF_Dict_GetItem (obj, "Kids",
                    HPDF_OCLASS_ARRAY);
    HPDF_Number count = (HPDF_Number)HPDF_Dict_GetItem (obj, "Count",
                    HPDF_OCLASS_NUMBER);
    HPDF_STATUS ret;

    HPDF_PTRACE((" HPDF_Pages_BeforeWrite\n"));

    if (!kids)
        return HPDF_SetError (obj->error, HPDF_PAGES_MISSING_KIDS_ENTRY, 0);

    if (count)
        count->value = GetPageCount (obj);
    else {
        count = HPDF_Number_New (obj->mmgr, GetPageCount (obj));
        if (!count)
            return HPDF_Error_GetCode (obj->error);

        if ((ret = HPDF_Dict_Add (obj, "Count", count)) != HPDF_OK)
            return ret;
    }

    return HPDF_OK;
}