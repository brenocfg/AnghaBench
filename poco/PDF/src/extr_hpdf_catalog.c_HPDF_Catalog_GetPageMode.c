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
struct TYPE_2__ {int /*<<< orphan*/  value; } ;
typedef  size_t HPDF_UINT ;
typedef  int /*<<< orphan*/  HPDF_PageMode ;
typedef  TYPE_1__* HPDF_Name ;
typedef  int /*<<< orphan*/  HPDF_Catalog ;

/* Variables and functions */
 scalar_t__ HPDF_Dict_GetItem (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_OCLASS_NAME ; 
 scalar_t__* HPDF_PAGE_MODE_NAMES ; 
 int /*<<< orphan*/  HPDF_PAGE_MODE_USE_NONE ; 
 scalar_t__ HPDF_StrCmp (int /*<<< orphan*/ ,scalar_t__) ; 

HPDF_PageMode
HPDF_Catalog_GetPageMode  (HPDF_Catalog  catalog)
{
    HPDF_Name mode;
    HPDF_UINT i = 0;

    mode = (HPDF_Name)HPDF_Dict_GetItem (catalog, "PageMode", HPDF_OCLASS_NAME);
    if (!mode)
        return HPDF_PAGE_MODE_USE_NONE;

    while (HPDF_PAGE_MODE_NAMES[i]) {
        if (HPDF_StrCmp (mode->value, HPDF_PAGE_MODE_NAMES[i]) == 0)
            return (HPDF_PageMode)i;
        i++;
    }

    return HPDF_PAGE_MODE_USE_NONE;
}