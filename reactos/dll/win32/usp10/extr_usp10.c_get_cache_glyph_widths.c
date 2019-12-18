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
typedef  size_t WORD ;
struct TYPE_2__ {int /*<<< orphan*/ ** widths; } ;
typedef  TYPE_1__ ScriptCache ;
typedef  scalar_t__ SCRIPT_CACHE ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  ABC ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 size_t GLYPH_BLOCK_MASK ; 
 size_t GLYPH_BLOCK_SHIFT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline BOOL get_cache_glyph_widths(SCRIPT_CACHE *psc, WORD glyph, ABC *abc)
{
    static const ABC nil;
    ABC *block = ((ScriptCache *)*psc)->widths[glyph >> GLYPH_BLOCK_SHIFT];

    if (!block || !memcmp(&block[glyph & GLYPH_BLOCK_MASK], &nil, sizeof(ABC))) return FALSE;
    memcpy(abc, &block[glyph & GLYPH_BLOCK_MASK], sizeof(ABC));
    return TRUE;
}