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
struct iterations {scalar_t__ from; } ;
struct branch_entry {scalar_t__ from; } ;
typedef  int /*<<< orphan*/  chash ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CHASHBITS ; 
 int CHASHSZ ; 
 unsigned char NO_ENTRY ; 
 int PERF_MAX_BRANCH_DEPTH ; 
 int hash_64 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (struct iterations*,struct iterations*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,unsigned char,int) ; 
 int /*<<< orphan*/  save_iterations (struct iterations*,struct iterations*,int) ; 

__attribute__((used)) static int remove_loops(struct branch_entry *l, int nr,
			struct iterations *iter)
{
	int i, j, off;
	unsigned char chash[CHASHSZ];

	memset(chash, NO_ENTRY, sizeof(chash));

	BUG_ON(PERF_MAX_BRANCH_DEPTH > 255);

	for (i = 0; i < nr; i++) {
		int h = hash_64(l[i].from, CHASHBITS) % CHASHSZ;

		/* no collision handling for now */
		if (chash[h] == NO_ENTRY) {
			chash[h] = i;
		} else if (l[chash[h]].from == l[i].from) {
			bool is_loop = true;
			/* check if it is a real loop */
			off = 0;
			for (j = chash[h]; j < i && i + off < nr; j++, off++)
				if (l[j].from != l[i + off].from) {
					is_loop = false;
					break;
				}
			if (is_loop) {
				j = nr - (i + off);
				if (j > 0) {
					save_iterations(iter + i + off,
						l + i, off);

					memmove(iter + i, iter + i + off,
						j * sizeof(*iter));

					memmove(l + i, l + i + off,
						j * sizeof(*l));
				}

				nr -= off;
			}
		}
	}
	return nr;
}