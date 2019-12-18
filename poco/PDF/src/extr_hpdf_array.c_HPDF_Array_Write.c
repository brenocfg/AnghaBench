#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ count; } ;
struct TYPE_4__ {TYPE_2__* list; } ;
typedef  scalar_t__ HPDF_UINT ;
typedef  int /*<<< orphan*/  HPDF_Stream ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  int /*<<< orphan*/  HPDF_Encrypt ;
typedef  TYPE_1__* HPDF_Array ;

/* Variables and functions */
 void* HPDF_List_ItemAt (TYPE_2__*,scalar_t__) ; 
 scalar_t__ HPDF_OK ; 
 scalar_t__ HPDF_Obj_Write (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 scalar_t__ HPDF_Stream_WriteChar (int /*<<< orphan*/ ,char) ; 
 scalar_t__ HPDF_Stream_WriteStr (int /*<<< orphan*/ ,char*) ; 

HPDF_STATUS
HPDF_Array_Write  (HPDF_Array    array,
                   HPDF_Stream   stream,
                   HPDF_Encrypt  e)
{
    HPDF_UINT i;
    HPDF_STATUS ret;

    HPDF_PTRACE((" HPDF_Array_Write\n"));

    ret = HPDF_Stream_WriteStr (stream, "[ ");
    if (ret != HPDF_OK)
        return ret;

    for (i = 0; i < array->list->count; i++) {
        void * element = HPDF_List_ItemAt (array->list, i);

        ret = HPDF_Obj_Write (element, stream, e);
        if (ret != HPDF_OK)
            return ret;

        ret = HPDF_Stream_WriteChar (stream, ' ');
        if (ret != HPDF_OK)
            return ret;
    }

    ret = HPDF_Stream_WriteChar (stream, ']');

    return ret;
}