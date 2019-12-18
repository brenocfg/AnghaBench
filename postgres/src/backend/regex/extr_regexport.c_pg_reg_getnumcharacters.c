#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct colormap {int max; TYPE_1__* cd; } ;
struct guts {struct colormap cmap; } ;
struct TYPE_5__ {scalar_t__ re_magic; scalar_t__ re_guts; } ;
typedef  TYPE_2__ regex_t ;
struct TYPE_4__ {int flags; scalar_t__ nuchrs; int nschrs; } ;

/* Variables and functions */
 int PSEUDO ; 
 scalar_t__ REMAGIC ; 
 int /*<<< orphan*/  assert (int) ; 

int
pg_reg_getnumcharacters(const regex_t *regex, int co)
{
	struct colormap *cm;

	assert(regex != NULL && regex->re_magic == REMAGIC);
	cm = &((struct guts *) regex->re_guts)->cmap;

	if (co <= 0 || co > cm->max)	/* we reject 0 which is WHITE */
		return -1;
	if (cm->cd[co].flags & PSEUDO)	/* also pseudocolors (BOS etc) */
		return -1;

	/*
	 * If the color appears anywhere in the high colormap, treat its number of
	 * members as uncertain.  In principle we could determine all the specific
	 * chrs corresponding to each such entry, but it would be expensive
	 * (particularly if character class tests are required) and it doesn't
	 * seem worth it.
	 */
	if (cm->cd[co].nuchrs != 0)
		return -1;

	/* OK, return the known number of member chrs */
	return cm->cd[co].nschrs;
}