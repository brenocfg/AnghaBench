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
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int* unicount ; 
 int** unitable ; 

__attribute__((used)) static void addpair(int fp, int un)
{
  int i;

  if ( un <= 0xfffe )
    {
      /* Check it isn't a duplicate */

      for ( i = 0 ; i < unicount[fp] ; i++ )
	if ( unitable[fp][i] == un )
	  return;

      /* Add to list */

      if ( unicount[fp] > 254 )
	{
	  fprintf(stderr, "ERROR: Only 255 unicodes/glyph permitted!\n");
	  exit(EX_DATAERR);
	}

      unitable[fp][unicount[fp]] = un;
      unicount[fp]++;
    }

  /* otherwise: ignore */
}