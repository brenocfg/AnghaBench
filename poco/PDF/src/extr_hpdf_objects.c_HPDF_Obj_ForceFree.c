#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int obj_class; scalar_t__ obj_id; } ;
typedef  int /*<<< orphan*/  HPDF_UINT ;
typedef  TYPE_1__ HPDF_Obj_Header ;
typedef  int /*<<< orphan*/  HPDF_MMgr ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_Array_Free (void*) ; 
 int /*<<< orphan*/  HPDF_Binary_Free (void*) ; 
 int /*<<< orphan*/  HPDF_Dict_Free (void*) ; 
 int /*<<< orphan*/  HPDF_FreeMem (int /*<<< orphan*/ ,void*) ; 
 int HPDF_OCLASS_ANY ; 
#define  HPDF_OCLASS_ARRAY 131 
#define  HPDF_OCLASS_BINARY 130 
#define  HPDF_OCLASS_DICT 129 
#define  HPDF_OCLASS_STRING 128 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_String_Free (void*) ; 

void
HPDF_Obj_ForceFree  (HPDF_MMgr    mmgr,
                     void         *obj)
{
    HPDF_Obj_Header *header;

    HPDF_PTRACE((" HPDF_Obj_ForceFree\n"));

    if (!obj)
        return;

    header = (HPDF_Obj_Header *)obj;

    HPDF_PTRACE((" HPDF_Obj_ForceFree obj=0x%08X obj_id=0x%08X "
                    "obj_class=0x%08X\n",
                    (HPDF_UINT)obj, (HPDF_UINT)(header->obj_id),
                    (HPDF_UINT)(header->obj_class)));

    switch (header->obj_class & HPDF_OCLASS_ANY) {
        case HPDF_OCLASS_STRING:
            HPDF_String_Free (obj);
            break;
        case HPDF_OCLASS_BINARY:
            HPDF_Binary_Free (obj);
            break;
        case HPDF_OCLASS_ARRAY:
            HPDF_Array_Free (obj);
            break;
        case HPDF_OCLASS_DICT:
            HPDF_Dict_Free (obj);
            break;
        default:
            HPDF_FreeMem (mmgr, obj);
    }
}