#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_1__* list; } ;
struct TYPE_17__ {int /*<<< orphan*/  mmgr; int /*<<< orphan*/  attr; } ;
struct TYPE_16__ {TYPE_4__* ext_gstates; } ;
struct TYPE_15__ {scalar_t__ count; } ;
typedef  TYPE_2__* HPDF_PageAttr ;
typedef  TYPE_3__* HPDF_Page ;
typedef  TYPE_4__* HPDF_ExtGState ;
typedef  TYPE_4__* HPDF_Dict ;

/* Variables and functions */
 scalar_t__ HPDF_Dict_Add (TYPE_4__*,char*,TYPE_4__*) ; 
 char* HPDF_Dict_GetKeyByObj (TYPE_4__*,TYPE_4__*) ; 
 TYPE_4__* HPDF_Dict_New (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_IToA (char*,scalar_t__,char*) ; 
 int HPDF_LIMIT_MAX_NAME_LEN ; 
 int /*<<< orphan*/  HPDF_OCLASS_DICT ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 TYPE_4__* HPDF_Page_GetInheritableItem (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_StrCpy (char*,char*,char*) ; 

const char*
HPDF_Page_GetExtGStateName  (HPDF_Page       page,
                             HPDF_ExtGState  state)
{
    HPDF_PageAttr attr = (HPDF_PageAttr )page->attr;
    const char *key;

    HPDF_PTRACE((" HPDF_Page_GetExtGStateName\n"));

    if (!attr->ext_gstates) {
        HPDF_Dict resources;
        HPDF_Dict ext_gstates;

        resources = HPDF_Page_GetInheritableItem (page, "Resources",
                        HPDF_OCLASS_DICT);
        if (!resources)
            return NULL;

        ext_gstates = HPDF_Dict_New (page->mmgr);
        if (!ext_gstates)
            return NULL;

        if (HPDF_Dict_Add (resources, "ExtGState", ext_gstates) != HPDF_OK)
            return NULL;

        attr->ext_gstates = ext_gstates;
    }

    /* search ext_gstate-object from ext_gstate-resource */
    key = HPDF_Dict_GetKeyByObj (attr->ext_gstates, state);
    if (!key) {
        /* if the ext-gstate is not resisterd in ext-gstate resource, register
         *  to ext-gstate resource.
         */
        char ext_gstate_name[HPDF_LIMIT_MAX_NAME_LEN + 1];
        char *ptr;
        char *end_ptr = ext_gstate_name + HPDF_LIMIT_MAX_NAME_LEN;

        ptr = (char *)HPDF_StrCpy (ext_gstate_name, "E", end_ptr);
        HPDF_IToA (ptr, attr->ext_gstates->list->count + 1, end_ptr);

        if (HPDF_Dict_Add (attr->ext_gstates, ext_gstate_name, state) != HPDF_OK)
            return NULL;

        key = HPDF_Dict_GetKeyByObj (attr->ext_gstates, state);
    }

    return key;
}