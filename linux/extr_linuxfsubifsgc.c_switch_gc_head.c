#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ubifs_wbuf {scalar_t__ used; scalar_t__ offs; int /*<<< orphan*/  lnum; } ;
struct ubifs_info {int gc_lnum; scalar_t__ leb_size; TYPE_1__* jheads; } ;
struct TYPE_2__ {struct ubifs_wbuf wbuf; } ;

/* Variables and functions */
 size_t GCHD ; 
 int /*<<< orphan*/  dbg_gc (char*,int /*<<< orphan*/ ,scalar_t__,int,scalar_t__) ; 
 int ubifs_add_bud_to_log (struct ubifs_info*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 int ubifs_leb_unmap (struct ubifs_info*,int) ; 
 int ubifs_wbuf_seek_nolock (struct ubifs_wbuf*,int,int /*<<< orphan*/ ) ; 
 int ubifs_wbuf_sync_nolock (struct ubifs_wbuf*) ; 

__attribute__((used)) static int switch_gc_head(struct ubifs_info *c)
{
	int err, gc_lnum = c->gc_lnum;
	struct ubifs_wbuf *wbuf = &c->jheads[GCHD].wbuf;

	ubifs_assert(c, gc_lnum != -1);
	dbg_gc("switch GC head from LEB %d:%d to LEB %d (waste %d bytes)",
	       wbuf->lnum, wbuf->offs + wbuf->used, gc_lnum,
	       c->leb_size - wbuf->offs - wbuf->used);

	err = ubifs_wbuf_sync_nolock(wbuf);
	if (err)
		return err;

	/*
	 * The GC write-buffer was synchronized, we may safely unmap
	 * 'c->gc_lnum'.
	 */
	err = ubifs_leb_unmap(c, gc_lnum);
	if (err)
		return err;

	err = ubifs_add_bud_to_log(c, GCHD, gc_lnum, 0);
	if (err)
		return err;

	c->gc_lnum = -1;
	err = ubifs_wbuf_seek_nolock(wbuf, gc_lnum, 0);
	return err;
}