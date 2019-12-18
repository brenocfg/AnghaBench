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
struct TYPE_5__ {int /*<<< orphan*/  error; TYPE_1__ header; } ;
typedef  TYPE_2__* HPDF_NameTree ;
typedef  int /*<<< orphan*/  HPDF_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FALSE ; 
 int /*<<< orphan*/  HPDF_INVALID_OBJECT ; 
 int HPDF_OCLASS_DICT ; 
 int HPDF_OSUBCLASS_NAMETREE ; 
 int /*<<< orphan*/  HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_TRUE ; 

HPDF_BOOL
HPDF_NameTree_Validate  (HPDF_NameTree  nametree)
{
    if (!nametree)
        return HPDF_FALSE;

    if (nametree->header.obj_class != (HPDF_OSUBCLASS_NAMETREE |
                HPDF_OCLASS_DICT)) {
        HPDF_SetError (nametree->error, HPDF_INVALID_OBJECT, 0);
        return HPDF_FALSE;
    }

    return HPDF_TRUE;
}