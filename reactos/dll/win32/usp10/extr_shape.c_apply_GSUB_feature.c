#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_7__ {int lookup_count; int /*<<< orphan*/ * lookups; } ;
struct TYPE_6__ {scalar_t__ GSUB_Table; } ;
typedef  TYPE_1__ ScriptCache ;
typedef  int /*<<< orphan*/  SCRIPT_ANALYSIS ;
typedef  TYPE_2__ LoadedFeature ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  FEATURE_GSUB_TABLE ; 
 int GSUB_E_NOFEATURE ; 
 int OpenType_apply_GSUB_lookup (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int*) ; 
 int /*<<< orphan*/  TRACE (char*,int,int) ; 
 int /*<<< orphan*/  UpdateClusters (int,int,int,int,int /*<<< orphan*/ *) ; 
 int debugstr_an (char const*,int) ; 
 TYPE_2__* load_OT_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int apply_GSUB_feature(HDC hdc, SCRIPT_ANALYSIS *psa, ScriptCache* psc, WORD *pwOutGlyphs, int write_dir, INT* pcGlyphs, INT cChars, const char* feat, WORD *pwLogClust )
{
    if (psc->GSUB_Table)
    {
        LoadedFeature *feature;
        int lookup_index;

        feature = load_OT_feature(hdc, psa, psc, FEATURE_GSUB_TABLE, feat);
        if (!feature)
            return GSUB_E_NOFEATURE;

        TRACE("applying feature %s: %i lookups\n",debugstr_an(feat,4),feature->lookup_count);
        for (lookup_index = 0; lookup_index < feature->lookup_count; lookup_index++)
        {
            int i;

            if (write_dir > 0)
                i = 0;
            else
                i = *pcGlyphs-1;
            TRACE("applying lookup (%i/%i)\n",lookup_index,feature->lookup_count);
            while(i < *pcGlyphs && i >= 0)
            {
                INT nextIndex;
                INT prevCount = *pcGlyphs;

                nextIndex = OpenType_apply_GSUB_lookup(psc->GSUB_Table, feature->lookups[lookup_index], pwOutGlyphs, i, write_dir, pcGlyphs);
                if (*pcGlyphs != prevCount)
                {
                    UpdateClusters(nextIndex, *pcGlyphs - prevCount, write_dir, cChars, pwLogClust);
                    i = nextIndex;
                }
                else
                    i+=write_dir;
            }
        }
        return *pcGlyphs;
    }
    return GSUB_E_NOFEATURE;
}