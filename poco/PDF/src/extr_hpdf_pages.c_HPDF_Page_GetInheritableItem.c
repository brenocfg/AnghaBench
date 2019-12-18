#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  error; } ;
typedef  int /*<<< orphan*/  HPDF_UINT16 ;
typedef  TYPE_1__* HPDF_Pages ;
typedef  TYPE_1__* HPDF_Page ;
typedef  size_t HPDF_INT ;
typedef  scalar_t__ HPDF_BOOL ;

/* Variables and functions */
 void* HPDF_Dict_GetItem (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_FALSE ; 
 scalar_t__* HPDF_INHERITABLE_ENTRIES ; 
 int /*<<< orphan*/  HPDF_INVALID_PARAMETER ; 
 int /*<<< orphan*/  HPDF_OCLASS_DICT ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_StrCmp (char const*,scalar_t__) ; 
 scalar_t__ HPDF_TRUE ; 

void*
HPDF_Page_GetInheritableItem  (HPDF_Page          page,
                               const char   *key,
                               HPDF_UINT16        obj_class)
{
    HPDF_BOOL chk = HPDF_FALSE;
    HPDF_INT i = 0;
    void * obj;

    HPDF_PTRACE((" HPDF_Page_GetInheritableItem\n"));

    /* check whether the specified key is valid */
    while (HPDF_INHERITABLE_ENTRIES[i]) {
        if (HPDF_StrCmp (key, HPDF_INHERITABLE_ENTRIES[i]) == 0) {
            chk = HPDF_TRUE;
            break;
        }
        i++;
    }

    /* the key is not inheritable */
    if (chk != HPDF_TRUE) {
        HPDF_SetError (page->error, HPDF_INVALID_PARAMETER, 0);
        return NULL;
    }

    obj = HPDF_Dict_GetItem (page, key, obj_class);

    /* if resources of the object is NULL, search resources of parent
     * pages recursivly
     */
    if (!obj) {
        HPDF_Pages pages = HPDF_Dict_GetItem (page, "Parent", HPDF_OCLASS_DICT);
        while (pages) {
            obj = HPDF_Dict_GetItem (page, key, obj_class);

            if (obj)
                break;

            pages = HPDF_Dict_GetItem (pages, "Parent", HPDF_OCLASS_DICT);
        }
    }

    return obj;
}