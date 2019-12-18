#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  newOtTag; } ;
struct TYPE_4__ {size_t eScript; } ;
typedef  int /*<<< orphan*/  ScriptCache ;
typedef  TYPE_1__ SCRIPT_ANALYSIS ;
typedef  int /*<<< orphan*/  OPENTYPE_TAG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  OpenType_GetFontScriptTags (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 TYPE_3__* ShapingData ; 

__attribute__((used)) static inline BOOL get_GSUB_Indic2(SCRIPT_ANALYSIS *psa, ScriptCache *psc)
{
    OPENTYPE_TAG tag;
    HRESULT hr;
    int count = 0;

    hr = OpenType_GetFontScriptTags(psc, ShapingData[psa->eScript].newOtTag, 1, &tag, &count);

    return(SUCCEEDED(hr));
}