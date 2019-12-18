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
struct TYPE_7__ {unsigned int lookup_count; int /*<<< orphan*/ * lookups; } ;
struct TYPE_6__ {scalar_t__ fRTL; scalar_t__ fLogicalOrder; } ;
typedef  int /*<<< orphan*/  ScriptCache ;
typedef  TYPE_1__ SCRIPT_ANALYSIS ;
typedef  int /*<<< orphan*/  OUTLINETEXTMETRICW ;
typedef  TYPE_2__ LoadedFeature ;
typedef  int /*<<< orphan*/  LOGFONTW ;
typedef  int /*<<< orphan*/  GOFFSET ;

/* Variables and functions */
 scalar_t__ OpenType_apply_GPOS_lookup (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,TYPE_1__ const*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,unsigned int) ; 

__attribute__((used)) static void GPOS_apply_feature(const ScriptCache *psc, const OUTLINETEXTMETRICW *otm,
        const LOGFONTW *logfont, const SCRIPT_ANALYSIS *analysis, int *advance,
        const LoadedFeature *feature, const WORD *glyphs, int glyph_count, GOFFSET *goffset)
{
    int dir = analysis->fLogicalOrder && analysis->fRTL ? -1 : 1;
    unsigned int start_idx, i, j;

    TRACE("%i lookups\n", feature->lookup_count);

    start_idx = dir < 0 ? glyph_count - 1 : 0;
    for (i = 0; i < feature->lookup_count; i++)
    {
        for (j = 0; j < glyph_count; )
            j += OpenType_apply_GPOS_lookup(psc, otm, logfont, analysis, advance,
                    feature->lookups[i], glyphs, start_idx + dir * j, glyph_count, goffset);
    }
}