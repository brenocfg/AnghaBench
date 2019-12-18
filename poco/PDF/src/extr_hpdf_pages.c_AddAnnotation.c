#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  error; int /*<<< orphan*/  mmgr; } ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  TYPE_1__* HPDF_Page ;
typedef  TYPE_1__* HPDF_Array ;
typedef  TYPE_1__* HPDF_Annotation ;

/* Variables and functions */
 scalar_t__ HPDF_Array_Add (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* HPDF_Array_New (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Dict_Add (TYPE_1__*,char*,TYPE_1__*) ; 
 TYPE_1__* HPDF_Dict_GetItem (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Error_GetCode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_OCLASS_ARRAY ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

__attribute__((used)) static HPDF_STATUS
AddAnnotation  (HPDF_Page        page,
                HPDF_Annotation  annot)
{
    HPDF_Array array;
    HPDF_STATUS ret = HPDF_OK;

    HPDF_PTRACE((" HPDF_Pages\n"));

    /* find "Annots" entry */
    array = HPDF_Dict_GetItem (page, "Annots", HPDF_OCLASS_ARRAY);

    if (!array) {
        array = HPDF_Array_New (page->mmgr);
        if (!array)
            return HPDF_Error_GetCode (page->error);

        ret = HPDF_Dict_Add (page, "Annots", array);
        if (ret != HPDF_OK)
            return ret;
    }
    
    if ((ret = HPDF_Array_Add (array, annot)) != HPDF_OK)
       return ret;

    /* Add Parent to the annotation  */
    ret = HPDF_Dict_Add( annot, "P", page);

    return ret;
}