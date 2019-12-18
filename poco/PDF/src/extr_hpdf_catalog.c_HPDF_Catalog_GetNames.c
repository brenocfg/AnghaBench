#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ * HPDF_NameDict ;
typedef  int /*<<< orphan*/  HPDF_Catalog ;

/* Variables and functions */
 int /*<<< orphan*/ * HPDF_Dict_GetItem (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_OCLASS_DICT ; 

HPDF_NameDict
HPDF_Catalog_GetNames  (HPDF_Catalog catalog)
{
    if (!catalog)
        return NULL;
    return HPDF_Dict_GetItem (catalog, "Names", HPDF_OCLASS_DICT);
}