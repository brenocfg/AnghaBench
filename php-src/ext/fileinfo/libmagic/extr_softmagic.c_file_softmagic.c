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
typedef  scalar_t__ uint16_t ;
struct mlist {int /*<<< orphan*/  nmagic; int /*<<< orphan*/  magic; struct mlist* next; } ;
struct magic_set {struct mlist** mlist; } ;
struct buffer {int dummy; } ;

/* Variables and functions */
 int match (struct magic_set*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer const*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
file_softmagic(struct magic_set *ms, const struct buffer *b,
    uint16_t *indir_count, uint16_t *name_count, int mode, int text)
{
	struct mlist *ml;
	int rv, printed_something = 0, need_separator = 0;
	uint16_t nc, ic;

	if (name_count == NULL) {
		nc = 0;
		name_count = &nc;
	}
	if (indir_count == NULL) {
		ic = 0;
		indir_count = &ic;
	}

	for (ml = ms->mlist[0]->next; ml != ms->mlist[0]; ml = ml->next)
		if ((rv = match(ms, ml->magic, ml->nmagic, b, 0, mode,
		    text, 0, indir_count, name_count,
		    &printed_something, &need_separator, NULL, NULL)) != 0)
			return rv;

	return 0;
}