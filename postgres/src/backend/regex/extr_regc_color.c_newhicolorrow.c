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
struct colormap {int hiarrayrows; int maxarrayrows; int hiarraycols; size_t* hicolormap; TYPE_1__* cd; } ;
typedef  size_t color ;
struct TYPE_2__ {int /*<<< orphan*/  nuchrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CERR (int /*<<< orphan*/ ) ; 
 int INT_MAX ; 
 scalar_t__ REALLOC (size_t*,int) ; 
 int /*<<< orphan*/  REG_ESPACE ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t*,int) ; 

__attribute__((used)) static int
newhicolorrow(struct colormap *cm,
			  int oldrow)
{
	int			newrow = cm->hiarrayrows;
	color	   *newrowptr;
	int			i;

	/* Assign a fresh array row index, enlarging storage if needed */
	if (newrow >= cm->maxarrayrows)
	{
		color	   *newarray;

		if (cm->maxarrayrows >= INT_MAX / (cm->hiarraycols * 2))
		{
			CERR(REG_ESPACE);
			return 0;
		}
		newarray = (color *) REALLOC(cm->hicolormap,
									 cm->maxarrayrows * 2 *
									 cm->hiarraycols * sizeof(color));
		if (newarray == NULL)
		{
			CERR(REG_ESPACE);
			return 0;
		}
		cm->hicolormap = newarray;
		cm->maxarrayrows *= 2;
	}
	cm->hiarrayrows++;

	/* Copy old row data */
	newrowptr = &cm->hicolormap[newrow * cm->hiarraycols];
	memcpy(newrowptr,
		   &cm->hicolormap[oldrow * cm->hiarraycols],
		   cm->hiarraycols * sizeof(color));

	/* Increase color reference counts to reflect new colormap entries */
	for (i = 0; i < cm->hiarraycols; i++)
		cm->cd[newrowptr[i]].nuchrs++;

	return newrow;
}