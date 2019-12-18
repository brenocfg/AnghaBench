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
struct vars {int dummy; } ;
struct colormap {int maxarrayrows; int hiarrayrows; int hiarraycols; int /*<<< orphan*/ * hicolormap; int /*<<< orphan*/ * cmranges; scalar_t__ numcmranges; int /*<<< orphan*/ * classbits; int /*<<< orphan*/ * locolormap; struct colordesc* cd; scalar_t__ free; scalar_t__ max; struct colordesc* cdspace; int /*<<< orphan*/  ncds; struct vars* v; int /*<<< orphan*/  magic; } ;
struct colordesc {int nschrs; int nuchrs; int firstchr; scalar_t__ flags; int /*<<< orphan*/ * arcs; int /*<<< orphan*/  sub; } ;
typedef  int /*<<< orphan*/  color ;

/* Variables and functions */
 int /*<<< orphan*/  CERR (int /*<<< orphan*/ ) ; 
 int CHR_MIN ; 
 int /*<<< orphan*/  CMMAGIC ; 
 scalar_t__ MALLOC (int) ; 
 int MAX_SIMPLE_CHR ; 
 int /*<<< orphan*/  NINLINECDS ; 
 int /*<<< orphan*/  NOSUB ; 
 int /*<<< orphan*/  REG_ESPACE ; 
 int /*<<< orphan*/  WHITE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
initcm(struct vars *v,
	   struct colormap *cm)
{
	struct colordesc *cd;

	cm->magic = CMMAGIC;
	cm->v = v;

	cm->ncds = NINLINECDS;
	cm->cd = cm->cdspace;
	cm->max = 0;
	cm->free = 0;

	cd = cm->cd;				/* cm->cd[WHITE] */
	cd->nschrs = MAX_SIMPLE_CHR - CHR_MIN + 1;
	cd->nuchrs = 1;
	cd->sub = NOSUB;
	cd->arcs = NULL;
	cd->firstchr = CHR_MIN;
	cd->flags = 0;

	cm->locolormap = (color *)
		MALLOC((MAX_SIMPLE_CHR - CHR_MIN + 1) * sizeof(color));
	if (cm->locolormap == NULL)
	{
		CERR(REG_ESPACE);
		cm->cmranges = NULL;	/* prevent failure during freecm */
		cm->hicolormap = NULL;
		return;
	}
	/* this memset relies on WHITE being zero: */
	memset(cm->locolormap, WHITE,
		   (MAX_SIMPLE_CHR - CHR_MIN + 1) * sizeof(color));

	memset(cm->classbits, 0, sizeof(cm->classbits));
	cm->numcmranges = 0;
	cm->cmranges = NULL;
	cm->maxarrayrows = 4;		/* arbitrary initial allocation */
	cm->hiarrayrows = 1;		/* but we have only one row/col initially */
	cm->hiarraycols = 1;
	cm->hicolormap = (color *) MALLOC(cm->maxarrayrows * sizeof(color));
	if (cm->hicolormap == NULL)
	{
		CERR(REG_ESPACE);
		return;
	}
	/* initialize the "all other characters" row to WHITE */
	cm->hicolormap[0] = WHITE;
}