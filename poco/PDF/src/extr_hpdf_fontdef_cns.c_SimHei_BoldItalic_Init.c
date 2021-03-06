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
typedef  scalar_t__ HPDF_STATUS ;
typedef  int /*<<< orphan*/  HPDF_FontDef ;

/* Variables and functions */
 scalar_t__ HPDF_CIDFontDef_ChangeStyle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_TRUE ; 
 scalar_t__ SimHei_Init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HPDF_STATUS
SimHei_BoldItalic_Init  (HPDF_FontDef   fontdef)
{
    HPDF_STATUS ret = SimHei_Init (fontdef);

    if (ret != HPDF_OK)
        return ret;

    return HPDF_CIDFontDef_ChangeStyle (fontdef, HPDF_TRUE, HPDF_TRUE);
}