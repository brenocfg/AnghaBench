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
struct r_magic {int dummy; } ;
struct mlist {int /*<<< orphan*/  nmagic; int /*<<< orphan*/  mapped; struct r_magic* magic; struct mlist* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  file_delmagic (struct r_magic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct mlist*) ; 

__attribute__((used)) static void free_mlist(struct mlist *mlist) {
	struct mlist *ml;
	if (!mlist) {
		return;
	}
	for (ml = mlist->next; ml != mlist;) {
		struct mlist *next = ml->next;
		struct r_magic *mg = ml->magic;
		file_delmagic (mg, ml->mapped, ml->nmagic);
		free (ml);
		ml = next;
	}
	free (ml);
}