#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct mlist {int /*<<< orphan*/  nmagic; int /*<<< orphan*/  magic; struct mlist* next; } ;
struct TYPE_4__ {struct mlist* mlist; } ;
typedef  TYPE_1__ RMagic ;

/* Variables and functions */
 int match (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int) ; 

int file_softmagic(RMagic *ms, const ut8 *buf, size_t nbytes, int mode) {
	struct mlist *ml;
	int rv;
	for (ml = ms->mlist->next; ml != ms->mlist; ml = ml->next) {
		if ((rv = match(ms, ml->magic, ml->nmagic, buf, nbytes, mode)) != 0) {
			return rv;
		}
	}
	return 0;
}