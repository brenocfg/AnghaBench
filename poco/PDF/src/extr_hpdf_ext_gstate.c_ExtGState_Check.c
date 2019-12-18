#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int obj_class; } ;
struct TYPE_6__ {int /*<<< orphan*/  error; TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_2__* HPDF_ExtGState ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_EXT_GSTATE_READ_ONLY ; 
 int /*<<< orphan*/  HPDF_ExtGState_Validate (TYPE_2__*) ; 
 int /*<<< orphan*/  HPDF_INVALID_OBJECT ; 
 int HPDF_OCLASS_DICT ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int HPDF_OSUBCLASS_EXT_GSTATE_R ; 
 int /*<<< orphan*/  HPDF_RaiseError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HPDF_STATUS
ExtGState_Check  (HPDF_ExtGState  ext_gstate)
{
    if (!HPDF_ExtGState_Validate (ext_gstate))
        return HPDF_INVALID_OBJECT;
    
    if (ext_gstate->header.obj_class == 
            (HPDF_OSUBCLASS_EXT_GSTATE_R | HPDF_OCLASS_DICT))
        return HPDF_RaiseError (ext_gstate->error, HPDF_EXT_GSTATE_READ_ONLY,
                0);

    return HPDF_OK;
}