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
struct ts_bm {int* bad_shift; int patlen; size_t* pattern; int* good_shift; } ;

/* Variables and functions */
 int ASIZE ; 
 int TS_IGNORECASE ; 
 scalar_t__ subpattern (size_t*,int,int,int) ; 
 size_t tolower (size_t) ; 

__attribute__((used)) static void compute_prefix_tbl(struct ts_bm *bm, int flags)
{
	int i, j, g;

	for (i = 0; i < ASIZE; i++)
		bm->bad_shift[i] = bm->patlen;
	for (i = 0; i < bm->patlen - 1; i++) {
		bm->bad_shift[bm->pattern[i]] = bm->patlen - 1 - i;
		if (flags & TS_IGNORECASE)
			bm->bad_shift[tolower(bm->pattern[i])]
			    = bm->patlen - 1 - i;
	}

	/* Compute the good shift array, used to match reocurrences 
	 * of a subpattern */
	bm->good_shift[0] = 1;
	for (i = 1; i < bm->patlen; i++)
		bm->good_shift[i] = bm->patlen;
        for (i = bm->patlen-1, g = 1; i > 0; g++, i--) {
		for (j = i-1; j >= 1-g ; j--)
			if (subpattern(bm->pattern, i, j, g)) {
				bm->good_shift[g] = bm->patlen-j-g;
				break;
			}
	}
}