#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  error; int /*<<< orphan*/  mmgr; } ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_1__* HPDF_Dict ;
typedef  int /*<<< orphan*/ * HPDF_Array ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_Array_Add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * HPDF_Array_New (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Dict_Add (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HPDF_Dict_GetItem (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Error_GetCode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_OCLASS_ARRAY ; 
 int /*<<< orphan*/  HPDF_OK ; 

HPDF_STATUS
HPDF_Dict_Add_FilterParams(HPDF_Dict    dict, HPDF_Dict filterParam)
{
    HPDF_Array paramArray;
    /* prepare params object */
    paramArray = HPDF_Dict_GetItem (dict, "DecodeParms",
                                              HPDF_OCLASS_ARRAY);
    if(paramArray==NULL) {
        paramArray = HPDF_Array_New (dict->mmgr);
       if (!paramArray)
            return HPDF_Error_GetCode (dict->error);

        /* add parameters */
        HPDF_Dict_Add(dict, "DecodeParms", paramArray);
    }
    HPDF_Array_Add(paramArray, filterParam);
    return HPDF_OK;
}