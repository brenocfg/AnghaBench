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
struct TYPE_2__ {int obj_class; } ;
typedef  int /*<<< orphan*/  HPDF_UINT ;
typedef  int /*<<< orphan*/  HPDF_Stream ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_1__ HPDF_Obj_Header ;
typedef  int /*<<< orphan*/  HPDF_Encrypt ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_Array_Write (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Binary_Write (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Boolean_Write (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Dict_Write (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_ERR_UNKNOWN_CLASS ; 
 int /*<<< orphan*/  HPDF_Name_Write (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Number_Write (void*,int /*<<< orphan*/ ) ; 
 int HPDF_OCLASS_ANY ; 
#define  HPDF_OCLASS_ARRAY 136 
#define  HPDF_OCLASS_BINARY 135 
#define  HPDF_OCLASS_BOOLEAN 134 
#define  HPDF_OCLASS_DICT 133 
#define  HPDF_OCLASS_NAME 132 
#define  HPDF_OCLASS_NULL 131 
#define  HPDF_OCLASS_NUMBER 130 
#define  HPDF_OCLASS_REAL 129 
#define  HPDF_OCLASS_STRING 128 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_Real_Write (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Stream_WriteStr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  HPDF_String_Write (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HPDF_STATUS
HPDF_Obj_WriteValue  (void          *obj,
                      HPDF_Stream   stream,
                      HPDF_Encrypt  e)
{
    HPDF_Obj_Header *header;
    HPDF_STATUS ret;

    HPDF_PTRACE((" HPDF_Obj_WriteValue\n"));

    header = (HPDF_Obj_Header *)obj;

    HPDF_PTRACE((" HPDF_Obj_WriteValue obj=0x%08X obj_class=0x%04X\n",
            (HPDF_UINT)obj, (HPDF_UINT)header->obj_class));

    switch (header->obj_class & HPDF_OCLASS_ANY) {
        case HPDF_OCLASS_NAME:
            ret = HPDF_Name_Write (obj, stream);
            break;
        case HPDF_OCLASS_NUMBER:
            ret = HPDF_Number_Write (obj, stream);
            break;
        case HPDF_OCLASS_REAL:
            ret = HPDF_Real_Write (obj, stream);
            break;
        case HPDF_OCLASS_STRING:
            ret = HPDF_String_Write (obj, stream, e);
            break;
        case HPDF_OCLASS_BINARY:
            ret = HPDF_Binary_Write (obj, stream, e);
            break;
        case HPDF_OCLASS_ARRAY:
            ret = HPDF_Array_Write (obj, stream, e);
            break;
        case HPDF_OCLASS_DICT:
            ret = HPDF_Dict_Write (obj, stream, e);
            break;
        case HPDF_OCLASS_BOOLEAN:
            ret = HPDF_Boolean_Write (obj, stream);
            break;
        case HPDF_OCLASS_NULL:
            ret = HPDF_Stream_WriteStr (stream, "null");
            break;
        default:
            ret = HPDF_ERR_UNKNOWN_CLASS;
    }

    return ret;
}