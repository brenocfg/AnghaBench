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
typedef  scalar_t__ LONG ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 scalar_t__ ColorCmp (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

__attribute__((used)) static INT countDiffRLE8(const WORD *lpP, const WORD *lpA, const WORD *lpB, INT pos, LONG lDist, LONG width)
{
  INT count;

  for (count = 0; pos < width; pos++, count++) {
    if (ColorCmp(lpA[pos], lpB[pos]) <= lDist) {
      /* diff at end? -- look-ahead for some more encodable pixel */
      if (pos + 1 < width && ColorCmp(lpB[pos], lpB[pos+1]) <= lDist)
	return count - 1;
      if (pos + 2 < width && ColorCmp(lpB[pos+1], lpB[pos+2]) <= lDist)
	return count - 1;
    } else if (lpP != NULL && ColorCmp(lpP[pos], lpB[pos]) <= lDist) {
      /* 'compare' with previous frame for end of diff */
      INT count2 = 0;

      for (count2 = 0, pos++; pos < width && count2 <= 5; pos++, count2++) {
	if (ColorCmp(lpP[pos], lpB[pos]) > lDist)
	  break;
      }
      if (count2 > 4)
	return count;

      pos -= count2;
    }
  }

  return count;
}