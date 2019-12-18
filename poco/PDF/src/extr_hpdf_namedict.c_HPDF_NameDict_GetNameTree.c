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
typedef  int /*<<< orphan*/ * HPDF_NameTree ;
typedef  size_t HPDF_NameDictKey ;
typedef  int /*<<< orphan*/  HPDF_NameDict ;

/* Variables and functions */
 int /*<<< orphan*/ * HPDF_Dict_GetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * HPDF_NAMEDICT_KEYS ; 
 int /*<<< orphan*/  HPDF_OCLASS_DICT ; 

HPDF_NameTree
HPDF_NameDict_GetNameTree  (HPDF_NameDict     namedict,
                            HPDF_NameDictKey  key)
{
    if (!namedict)
        return NULL;
    return HPDF_Dict_GetItem (namedict, HPDF_NAMEDICT_KEYS[key], HPDF_OCLASS_DICT);
}