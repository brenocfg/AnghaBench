#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  error; TYPE_1__* list; } ;
struct TYPE_7__ {int obj_class; } ;
struct TYPE_6__ {int count; } ;
typedef  scalar_t__ HPDF_Page ;
typedef  TYPE_2__ HPDF_Obj_Header ;
typedef  TYPE_3__* HPDF_Destination ;
typedef  int /*<<< orphan*/  HPDF_BOOL ;

/* Variables and functions */
 scalar_t__ HPDF_Array_GetItem (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_FALSE ; 
 int /*<<< orphan*/  HPDF_INVALID_PAGE ; 
 int HPDF_OCLASS_ARRAY ; 
 int /*<<< orphan*/  HPDF_OCLASS_DICT ; 
 int HPDF_OSUBCLASS_DESTINATION ; 
 int /*<<< orphan*/  HPDF_Page_Validate (scalar_t__) ; 
 int /*<<< orphan*/  HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_TRUE ; 

HPDF_BOOL
HPDF_Destination_Validate (HPDF_Destination  dst)
{
    HPDF_Obj_Header *header = (HPDF_Obj_Header *)dst;
    HPDF_Page target;

    if (!dst || header->obj_class !=
                (HPDF_OCLASS_ARRAY | HPDF_OSUBCLASS_DESTINATION))
        return HPDF_FALSE;

    /* destination-types not defined. */
    if (dst->list->count < 2)
        return HPDF_FALSE;

    target = (HPDF_Page)HPDF_Array_GetItem (dst, 0, HPDF_OCLASS_DICT);
    if (!HPDF_Page_Validate (target)) {
	    HPDF_SetError (dst->error, HPDF_INVALID_PAGE, 0);
        return HPDF_FALSE;
    }

    return HPDF_TRUE;
}