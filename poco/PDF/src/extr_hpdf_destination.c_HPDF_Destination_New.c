#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  obj_class; } ;
struct TYPE_13__ {TYPE_1__ header; } ;
struct TYPE_12__ {int /*<<< orphan*/  error; } ;
typedef  int /*<<< orphan*/  HPDF_Xref ;
typedef  int /*<<< orphan*/  HPDF_Page ;
typedef  TYPE_2__* HPDF_MMgr ;
typedef  size_t HPDF_INT ;
typedef  TYPE_3__* HPDF_Destination ;

/* Variables and functions */
 scalar_t__ HPDF_Array_Add (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Array_AddName (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* HPDF_Array_New (TYPE_2__*) ; 
 int /*<<< orphan*/ * HPDF_DESTINATION_TYPE_NAMES ; 
 scalar_t__ HPDF_FIT ; 
 int /*<<< orphan*/  HPDF_INVALID_PAGE ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_OSUBCLASS_DESTINATION ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_Page_Validate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Xref_Add (int /*<<< orphan*/ ,TYPE_3__*) ; 

HPDF_Destination
HPDF_Destination_New  (HPDF_MMgr   mmgr,
                       HPDF_Page   target,
                       HPDF_Xref   xref)
{
    HPDF_Destination dst;

    HPDF_PTRACE((" HPDF_Destination_New\n"));

    if (!HPDF_Page_Validate (target)) {
        HPDF_SetError (mmgr->error, HPDF_INVALID_PAGE, 0);
        return NULL;
    }

    dst = HPDF_Array_New (mmgr);
    if (!dst)
        return NULL;

    dst->header.obj_class |= HPDF_OSUBCLASS_DESTINATION;

    if (HPDF_Xref_Add (xref, dst) != HPDF_OK)
        return NULL;

    /* first item of array must be target page */
    if (HPDF_Array_Add (dst, target) != HPDF_OK)
        return NULL;

    /* default type is HPDF_FIT */
    if (HPDF_Array_AddName (dst,
            HPDF_DESTINATION_TYPE_NAMES[(HPDF_INT)HPDF_FIT]) != HPDF_OK)
        return NULL;

    return dst;
}