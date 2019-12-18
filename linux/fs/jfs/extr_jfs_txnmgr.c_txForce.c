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
struct tlock {int type; int flag; struct metapage* mp; scalar_t__ next; } ;
struct tblock {scalar_t__ next; } ;
struct metapage {int xflag; int nohomeok; int /*<<< orphan*/  flag; } ;
typedef  scalar_t__ lid_t ;

/* Variables and functions */
 int COMMIT_PAGE ; 
 int /*<<< orphan*/  META_dirty ; 
 int /*<<< orphan*/  META_sync ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  force_metapage (struct metapage*) ; 
 struct tlock* lid_to_tlock (scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tlckBTROOT ; 
 int tlckWRITEPAGE ; 

__attribute__((used)) static void txForce(struct tblock * tblk)
{
	struct tlock *tlck;
	lid_t lid, next;
	struct metapage *mp;

	/*
	 * reverse the order of transaction tlocks in
	 * careful update order of address index pages
	 * (right to left, bottom up)
	 */
	tlck = lid_to_tlock(tblk->next);
	lid = tlck->next;
	tlck->next = 0;
	while (lid) {
		tlck = lid_to_tlock(lid);
		next = tlck->next;
		tlck->next = tblk->next;
		tblk->next = lid;
		lid = next;
	}

	/*
	 * synchronously write the page, and
	 * hold the page for txUpdateMap();
	 */
	for (lid = tblk->next; lid; lid = next) {
		tlck = lid_to_tlock(lid);
		next = tlck->next;

		if ((mp = tlck->mp) != NULL &&
		    (tlck->type & tlckBTROOT) == 0) {
			assert(mp->xflag & COMMIT_PAGE);

			if (tlck->flag & tlckWRITEPAGE) {
				tlck->flag &= ~tlckWRITEPAGE;

				/* do not release page to freelist */
				force_metapage(mp);
#if 0
				/*
				 * The "right" thing to do here is to
				 * synchronously write the metadata.
				 * With the current implementation this
				 * is hard since write_metapage requires
				 * us to kunmap & remap the page.  If we
				 * have tlocks pointing into the metadata
				 * pages, we don't want to do this.  I think
				 * we can get by with synchronously writing
				 * the pages when they are released.
				 */
				assert(mp->nohomeok);
				set_bit(META_dirty, &mp->flag);
				set_bit(META_sync, &mp->flag);
#endif
			}
		}
	}
}