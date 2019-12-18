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
struct colormap {int hiarraycols; int maxarrayrows; size_t* hicolormap; int hiarrayrows; TYPE_1__* cd; } ;
typedef  size_t color ;
struct TYPE_2__ {int /*<<< orphan*/  nuchrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CERR (int /*<<< orphan*/ ) ; 
 int INT_MAX ; 
 scalar_t__ REALLOC (size_t*,int) ; 
 int /*<<< orphan*/  REG_ESPACE ; 

__attribute__((used)) static void
newhicolorcols(struct colormap *cm)
{
	color	   *newarray;
	int			r,
				c;

	if (cm->hiarraycols >= INT_MAX / (cm->maxarrayrows * 2))
	{
		CERR(REG_ESPACE);
		return;
	}
	newarray = (color *) REALLOC(cm->hicolormap,
								 cm->maxarrayrows *
								 cm->hiarraycols * 2 * sizeof(color));
	if (newarray == NULL)
	{
		CERR(REG_ESPACE);
		return;
	}
	cm->hicolormap = newarray;

	/* Duplicate existing columns to the right, and increase ref counts */
	/* Must work backwards in the array because we realloc'd in place */
	for (r = cm->hiarrayrows - 1; r >= 0; r--)
	{
		color	   *oldrowptr = &newarray[r * cm->hiarraycols];
		color	   *newrowptr = &newarray[r * cm->hiarraycols * 2];
		color	   *newrowptr2 = newrowptr + cm->hiarraycols;

		for (c = 0; c < cm->hiarraycols; c++)
		{
			color		co = oldrowptr[c];

			newrowptr[c] = newrowptr2[c] = co;
			cm->cd[co].nuchrs++;
		}
	}

	cm->hiarraycols *= 2;
}