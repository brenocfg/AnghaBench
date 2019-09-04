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
struct pos {int pos; int len; } ;
struct line {int n; scalar_t__ e; } ;

/* Variables and functions */

__attribute__((used)) static int longest_match(struct line *a, struct line *b, struct pos *pos,
			 int a1, int a2, int b1, int b2, int *omi, int *omj)
{
	int mi = a1, mj = b1, mk = 0, mb = 0, i, j, k;

	for (i = a1; i < a2; i++) {
		/* skip things before the current block */
		for (j = a[i].n; j < b1; j = b[j].n) {
			;
		}

		/* loop through all lines match a[i] in b */
		for (; j < b2; j = b[j].n) {
			/* does this extend an earlier match? */
			if (i > a1 && j > b1 && pos[j - 1].pos == i - 1) {
				k = pos[j - 1].len + 1;
			} else {
				k = 1;
			}
			pos[j].pos = i;
			pos[j].len = k;

			/* best match so far? */
			if (k > mk) {
				mi = i;
				mj = j;
				mk = k;
			}
		}
	}

	if (mk) {
		mi = mi - mk + 1;
		mj = mj - mk + 1;
	}

	/* expand match to include neighboring popular lines */
	while (mi - mb > a1 && mj - mb > b1 &&
		a[mi - mb - 1].e == b[mj - mb - 1].e) {
		mb++;
	}
	while (mi + mk < a2 && mj + mk < b2 &&
		a[mi + mk].e == b[mj + mk].e) {
		mk++;
	}

	*omi = mi - mb;
	*omj = mj - mb;

	return mk + mb;
}