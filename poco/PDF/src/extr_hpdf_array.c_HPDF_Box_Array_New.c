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
struct TYPE_3__ {int /*<<< orphan*/  top; int /*<<< orphan*/  right; int /*<<< orphan*/  bottom; int /*<<< orphan*/  left; } ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  int /*<<< orphan*/  HPDF_MMgr ;
typedef  TYPE_1__ HPDF_Box ;
typedef  int /*<<< orphan*/ * HPDF_Array ;

/* Variables and functions */
 scalar_t__ HPDF_Array_Add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Array_Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HPDF_Array_New (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_Real_New (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HPDF_Array
HPDF_Box_Array_New  (HPDF_MMgr  mmgr,
                     HPDF_Box   box)
{
    HPDF_Array  obj;
    HPDF_STATUS ret = HPDF_OK;

    HPDF_PTRACE((" HPDF_Box_Array_New\n"));

    obj = HPDF_Array_New (mmgr);
    if (!obj)
        return NULL;

    ret += HPDF_Array_Add (obj, HPDF_Real_New (mmgr, box.left));
    ret += HPDF_Array_Add (obj, HPDF_Real_New (mmgr, box.bottom));
    ret += HPDF_Array_Add (obj, HPDF_Real_New (mmgr, box.right));
    ret += HPDF_Array_Add (obj, HPDF_Real_New (mmgr, box.top));

    if (ret != HPDF_OK) {
        HPDF_Array_Free (obj);
        return NULL;
    }

    return obj;
}