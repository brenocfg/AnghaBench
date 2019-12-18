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
typedef  int /*<<< orphan*/  WORD ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  UpdateClusters (int,int,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void insert_glyph(WORD *pwGlyphs, INT *pcGlyphs, INT cChars, INT write_dir, WORD glyph, INT index, WORD *pwLogClust)
{
    int i;
    for (i = *pcGlyphs; i>=index; i--)
        pwGlyphs[i+1] = pwGlyphs[i];
    pwGlyphs[index] = glyph;
    *pcGlyphs = *pcGlyphs+1;
    if (write_dir < 0)
        UpdateClusters(index-3, 1, write_dir, cChars, pwLogClust);
    else
        UpdateClusters(index, 1, write_dir, cChars, pwLogClust);
}