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
struct TYPE_4__ {int obj_class; } ;
struct TYPE_5__ {TYPE_1__ header; } ;
typedef  TYPE_2__* HPDF_ExtGState ;
typedef  int /*<<< orphan*/  HPDF_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FALSE ; 
 int HPDF_OCLASS_DICT ; 
 int HPDF_OSUBCLASS_EXT_GSTATE ; 
 int HPDF_OSUBCLASS_EXT_GSTATE_R ; 
 int /*<<< orphan*/  HPDF_TRUE ; 

HPDF_BOOL
HPDF_ExtGState_Validate  (HPDF_ExtGState  ext_gstate)
{
    if (!ext_gstate || (ext_gstate->header.obj_class != 
                (HPDF_OSUBCLASS_EXT_GSTATE | HPDF_OCLASS_DICT) &&
                ext_gstate->header.obj_class !=
                 (HPDF_OSUBCLASS_EXT_GSTATE_R | HPDF_OCLASS_DICT)))
        return HPDF_FALSE;

    return HPDF_TRUE;
}