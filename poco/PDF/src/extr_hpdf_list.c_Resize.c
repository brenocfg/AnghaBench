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
struct TYPE_3__ {int count; void** obj; int block_siz; int /*<<< orphan*/  mmgr; int /*<<< orphan*/  error; } ;
typedef  int HPDF_UINT ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_1__* HPDF_List ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_Error_GetCode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_FreeMem (int /*<<< orphan*/ ,void**) ; 
 scalar_t__ HPDF_GetMem (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HPDF_INVALID_PARAMETER ; 
 int /*<<< orphan*/  HPDF_MemCpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

__attribute__((used)) static HPDF_STATUS
Resize  (HPDF_List   list,
         HPDF_UINT   count)
{
    void **new_obj;

    HPDF_PTRACE((" HPDF_List_Resize\n"));

    if (list->count >= count) {
        if (list->count == count)
            return HPDF_OK;
        else
            return HPDF_INVALID_PARAMETER;
    }

    new_obj = (void **)HPDF_GetMem (list->mmgr, count * sizeof(void *));

    if (!new_obj)
        return HPDF_Error_GetCode (list->error);

    if (list->obj)
        HPDF_MemCpy ((HPDF_BYTE *)new_obj, (HPDF_BYTE *)list->obj,
                list->block_siz * sizeof(void *));

    list->block_siz = count;
    if (list->obj)
        HPDF_FreeMem (list->mmgr, list->obj);
    list->obj = new_obj;

    return HPDF_OK;
}