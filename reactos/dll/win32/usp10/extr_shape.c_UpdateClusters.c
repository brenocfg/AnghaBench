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
typedef  int WORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int USP10_FindGlyphInLogClust (int*,int,int) ; 

__attribute__((used)) static void UpdateClusters(int nextIndex, int changeCount, int write_dir, int chars, WORD* pwLogClust )
{
    if (changeCount == 0)
        return;
    else
    {
        int cluster_dir = pwLogClust[0] < pwLogClust[chars-1] ? 1 : -1;
        int i;
        int target_glyph = nextIndex - write_dir;
        int target_index = -1;
        int replacing_glyph = -1;
        int changed = 0;

        if (changeCount > 0)
        {
            if (write_dir > 0)
                target_glyph = nextIndex - changeCount;
            else
                target_glyph = nextIndex + (changeCount + 1);
        }

        target_index = USP10_FindGlyphInLogClust(pwLogClust, chars, target_glyph);
        if (target_index == -1)
        {
            ERR("Unable to find target glyph\n");
            return;
        }

        if (changeCount < 0)
        {
            /* merge glyphs */
            for (i = target_index; i < chars && i >= 0; i += cluster_dir)
            {
                if (pwLogClust[i] == target_glyph)
                    continue;
                if(pwLogClust[i] == replacing_glyph)
                    pwLogClust[i] = target_glyph;
                else
                {
                    changed--;
                    if (changed >= changeCount)
                    {
                        replacing_glyph = pwLogClust[i];
                        pwLogClust[i] = target_glyph;
                    }
                    else
                        break;
                }
            }

            /* renumber trailing indexes */
            for (i = target_index; i < chars && i >= 0; i += cluster_dir)
            {
                if (pwLogClust[i] != target_glyph)
                    pwLogClust[i] += changeCount;
            }
        }
        else
        {
            for (i = target_index; i < chars && i >= 0; i += cluster_dir)
                pwLogClust[i] += changeCount;
        }
    }
}