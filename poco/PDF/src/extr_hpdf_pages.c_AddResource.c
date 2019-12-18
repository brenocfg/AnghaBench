#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  error; int /*<<< orphan*/  mmgr; } ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  TYPE_1__* HPDF_Page ;
typedef  TYPE_1__* HPDF_Dict ;
typedef  TYPE_1__* HPDF_Array ;

/* Variables and functions */
 scalar_t__ HPDF_Array_Add (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* HPDF_Array_New (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Dict_Add (TYPE_1__*,char*,TYPE_1__*) ; 
 TYPE_1__* HPDF_Dict_New (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Error_GetCode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Name_New (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

HPDF_STATUS
AddResource  (HPDF_Page  page)
{
    HPDF_STATUS ret = HPDF_OK;
    HPDF_Dict resource;
    HPDF_Array procset;

    HPDF_PTRACE((" HPDF_Page_AddResource\n"));

    resource = HPDF_Dict_New (page->mmgr);
    if (!resource)
        return HPDF_Error_GetCode (page->error);

    /* althoth ProcSet-entry is obsolete, add it to resouce for
     * compatibility
     */

    ret += HPDF_Dict_Add (page, "Resources", resource);

    procset = HPDF_Array_New (page->mmgr);
    if (!procset)
        return HPDF_Error_GetCode (page->error);

    if (HPDF_Dict_Add (resource, "ProcSet", procset) != HPDF_OK)
        return HPDF_Error_GetCode (resource->error);

    ret += HPDF_Array_Add (procset, HPDF_Name_New (page->mmgr, "PDF"));
    ret += HPDF_Array_Add (procset, HPDF_Name_New (page->mmgr, "Text"));
    ret += HPDF_Array_Add (procset, HPDF_Name_New (page->mmgr, "ImageB"));
    ret += HPDF_Array_Add (procset, HPDF_Name_New (page->mmgr, "ImageC"));
    ret += HPDF_Array_Add (procset, HPDF_Name_New (page->mmgr, "ImageI"));

    if (ret != HPDF_OK)
       return HPDF_Error_GetCode (procset->error);

    return HPDF_OK;
}