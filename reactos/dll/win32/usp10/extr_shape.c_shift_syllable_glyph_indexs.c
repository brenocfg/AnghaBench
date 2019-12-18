#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ start; scalar_t__ base; scalar_t__ end; scalar_t__ ralf; scalar_t__ blwf; scalar_t__ pref; } ;
typedef  TYPE_1__ IndicSyllable ;
typedef  scalar_t__ INT ;

/* Variables and functions */

__attribute__((used)) static inline void shift_syllable_glyph_indexs(IndicSyllable *glyph_index, INT index, INT shift)
{
    if (shift == 0)
        return;

    if (glyph_index->start > index)
        glyph_index->start += shift;
    if (glyph_index->base > index)
        glyph_index->base+= shift;
    if (glyph_index->end > index)
        glyph_index->end+= shift;
    if (glyph_index->ralf > index)
        glyph_index->ralf+= shift;
    if (glyph_index->blwf > index)
        glyph_index->blwf+= shift;
    if (glyph_index->pref > index)
        glyph_index->pref+= shift;
}