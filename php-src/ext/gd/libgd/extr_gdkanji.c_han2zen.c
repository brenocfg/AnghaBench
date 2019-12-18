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

/* Variables and functions */
 int FALSE ; 
 scalar_t__ IS_DAKU (int) ; 
 scalar_t__ IS_HANDAKU (int) ; 
 int TRUE ; 

__attribute__((used)) static void
han2zen (int *p1, int *p2)
{
  int c = *p1;
  int daku = FALSE;
  int handaku = FALSE;
  int mtable[][2] =
  {
    {129, 66},
    {129, 117},
    {129, 118},
    {129, 65},
    {129, 69},
    {131, 146},
    {131, 64},
    {131, 66},
    {131, 68},
    {131, 70},
    {131, 72},
    {131, 131},
    {131, 133},
    {131, 135},
    {131, 98},
    {129, 91},
    {131, 65},
    {131, 67},
    {131, 69},
    {131, 71},
    {131, 73},
    {131, 74},
    {131, 76},
    {131, 78},
    {131, 80},
    {131, 82},
    {131, 84},
    {131, 86},
    {131, 88},
    {131, 90},
    {131, 92},
    {131, 94},
    {131, 96},
    {131, 99},
    {131, 101},
    {131, 103},
    {131, 105},
    {131, 106},
    {131, 107},
    {131, 108},
    {131, 109},
    {131, 110},
    {131, 113},
    {131, 116},
    {131, 119},
    {131, 122},
    {131, 125},
    {131, 126},
    {131, 128},
    {131, 129},
    {131, 130},
    {131, 132},
    {131, 134},
    {131, 136},
    {131, 137},
    {131, 138},
    {131, 139},
    {131, 140},
    {131, 141},
    {131, 143},
    {131, 147},
    {129, 74},
    {129, 75}
  };

  if (*p2 == 222 && IS_DAKU (*p1))
    daku = TRUE;		/* Daku-ten */
  else if (*p2 == 223 && IS_HANDAKU (*p1))
    handaku = TRUE;		/* Han-daku-ten */

  *p1 = mtable[c - 161][0];
  *p2 = mtable[c - 161][1];

  if (daku)
    {
      if ((*p2 >= 74 && *p2 <= 103) || (*p2 >= 110 && *p2 <= 122))
	(*p2)++;
      else if (*p2 == 131 || *p2 == 69)
	*p2 = 148;
    }
  else if (handaku && *p2 >= 110 && *p2 <= 122)
    (*p2) += 2;
}