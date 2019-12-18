#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ubifs_lprops {int dirty; scalar_t__ free; int flags; } ;
struct ubifs_info {scalar_t__ leb_size; TYPE_1__* jheads; } ;
struct bud_entry {scalar_t__ free; int dirty; TYPE_2__* bud; } ;
struct TYPE_4__ {scalar_t__ start; size_t jhead; int /*<<< orphan*/  lnum; } ;
struct TYPE_3__ {int /*<<< orphan*/  wbuf; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ubifs_lprops const*) ; 
 int LPROPS_TAKEN ; 
 int PTR_ERR (struct ubifs_lprops const*) ; 
 int /*<<< orphan*/  dbg_gc (char*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  dbg_mnt (char*,int /*<<< orphan*/ ,scalar_t__,int,...) ; 
 struct ubifs_lprops* ubifs_change_lp (struct ubifs_info*,struct ubifs_lprops const*,scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_get_lprops (struct ubifs_info*) ; 
 struct ubifs_lprops* ubifs_lpt_lookup_dirty (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_release_lprops (struct ubifs_info*) ; 
 int ubifs_wbuf_seek_nolock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int set_bud_lprops(struct ubifs_info *c, struct bud_entry *b)
{
	const struct ubifs_lprops *lp;
	int err = 0, dirty;

	ubifs_get_lprops(c);

	lp = ubifs_lpt_lookup_dirty(c, b->bud->lnum);
	if (IS_ERR(lp)) {
		err = PTR_ERR(lp);
		goto out;
	}

	dirty = lp->dirty;
	if (b->bud->start == 0 && (lp->free != c->leb_size || lp->dirty != 0)) {
		/*
		 * The LEB was added to the journal with a starting offset of
		 * zero which means the LEB must have been empty. The LEB
		 * property values should be @lp->free == @c->leb_size and
		 * @lp->dirty == 0, but that is not the case. The reason is that
		 * the LEB had been garbage collected before it became the bud,
		 * and there was not commit inbetween. The garbage collector
		 * resets the free and dirty space without recording it
		 * anywhere except lprops, so if there was no commit then
		 * lprops does not have that information.
		 *
		 * We do not need to adjust free space because the scan has told
		 * us the exact value which is recorded in the replay entry as
		 * @b->free.
		 *
		 * However we do need to subtract from the dirty space the
		 * amount of space that the garbage collector reclaimed, which
		 * is the whole LEB minus the amount of space that was free.
		 */
		dbg_mnt("bud LEB %d was GC'd (%d free, %d dirty)", b->bud->lnum,
			lp->free, lp->dirty);
		dbg_gc("bud LEB %d was GC'd (%d free, %d dirty)", b->bud->lnum,
			lp->free, lp->dirty);
		dirty -= c->leb_size - lp->free;
		/*
		 * If the replay order was perfect the dirty space would now be
		 * zero. The order is not perfect because the journal heads
		 * race with each other. This is not a problem but is does mean
		 * that the dirty space may temporarily exceed c->leb_size
		 * during the replay.
		 */
		if (dirty != 0)
			dbg_mnt("LEB %d lp: %d free %d dirty replay: %d free %d dirty",
				b->bud->lnum, lp->free, lp->dirty, b->free,
				b->dirty);
	}
	lp = ubifs_change_lp(c, lp, b->free, dirty + b->dirty,
			     lp->flags | LPROPS_TAKEN, 0);
	if (IS_ERR(lp)) {
		err = PTR_ERR(lp);
		goto out;
	}

	/* Make sure the journal head points to the latest bud */
	err = ubifs_wbuf_seek_nolock(&c->jheads[b->bud->jhead].wbuf,
				     b->bud->lnum, c->leb_size - b->free);

out:
	ubifs_release_lprops(c);
	return err;
}