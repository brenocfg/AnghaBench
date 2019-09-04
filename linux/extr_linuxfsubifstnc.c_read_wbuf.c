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
struct ubifs_wbuf {int lnum; int offs; int buf; int /*<<< orphan*/  lock; struct ubifs_info* c; } ;
struct ubifs_info {int leb_cnt; int leb_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_io (char*,int,int,int) ; 
 int /*<<< orphan*/  memcpy (void*,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info const*,int) ; 
 int ubifs_leb_read (struct ubifs_info const*,int,void*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_wbuf(struct ubifs_wbuf *wbuf, void *buf, int len, int lnum,
		     int offs)
{
	const struct ubifs_info *c = wbuf->c;
	int rlen, overlap;

	dbg_io("LEB %d:%d, length %d", lnum, offs, len);
	ubifs_assert(c, wbuf && lnum >= 0 && lnum < c->leb_cnt && offs >= 0);
	ubifs_assert(c, !(offs & 7) && offs < c->leb_size);
	ubifs_assert(c, offs + len <= c->leb_size);

	spin_lock(&wbuf->lock);
	overlap = (lnum == wbuf->lnum && offs + len > wbuf->offs);
	if (!overlap) {
		/* We may safely unlock the write-buffer and read the data */
		spin_unlock(&wbuf->lock);
		return ubifs_leb_read(c, lnum, buf, offs, len, 0);
	}

	/* Don't read under wbuf */
	rlen = wbuf->offs - offs;
	if (rlen < 0)
		rlen = 0;

	/* Copy the rest from the write-buffer */
	memcpy(buf + rlen, wbuf->buf + offs + rlen - wbuf->offs, len - rlen);
	spin_unlock(&wbuf->lock);

	if (rlen > 0)
		/* Read everything that goes before write-buffer */
		return ubifs_leb_read(c, lnum, buf, offs, rlen, 0);

	return 0;
}