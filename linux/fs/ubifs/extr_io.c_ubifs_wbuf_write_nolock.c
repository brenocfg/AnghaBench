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
struct ubifs_wbuf {scalar_t__ lnum; int offs; int used; int avail; int size; void* buf; int (* sync_callback ) (struct ubifs_info*,scalar_t__,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  lock; scalar_t__ next_ino; int /*<<< orphan*/  jhead; int /*<<< orphan*/  io_mutex; struct ubifs_info* c; } ;
struct ubifs_info {scalar_t__ leb_cnt; int min_io_size; int leb_size; int max_write_size; int max_write_shift; scalar_t__ ro_error; int /*<<< orphan*/  space_fixup; int /*<<< orphan*/  ro_mount; int /*<<< orphan*/  ro_media; } ;
struct ubifs_ch {int /*<<< orphan*/  node_type; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int ENOSPC ; 
 int EROFS ; 
 int /*<<< orphan*/  cancel_wbuf_timer_nolock (struct ubifs_wbuf*) ; 
 int /*<<< orphan*/  dbg_io (char*,int,scalar_t__,int,...) ; 
 int dbg_jhead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_ntype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  new_wbuf_timer_nolock (struct ubifs_info*,struct ubifs_wbuf*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct ubifs_info*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  ubifs_dump_leb (struct ubifs_info*,scalar_t__) ; 
 int /*<<< orphan*/  ubifs_dump_node (struct ubifs_info*,void*) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,int,scalar_t__,int,int) ; 
 int ubifs_leb_write (struct ubifs_info*,scalar_t__,void*,int,int) ; 

int ubifs_wbuf_write_nolock(struct ubifs_wbuf *wbuf, void *buf, int len)
{
	struct ubifs_info *c = wbuf->c;
	int err, written, n, aligned_len = ALIGN(len, 8);

	dbg_io("%d bytes (%s) to jhead %s wbuf at LEB %d:%d", len,
	       dbg_ntype(((struct ubifs_ch *)buf)->node_type),
	       dbg_jhead(wbuf->jhead), wbuf->lnum, wbuf->offs + wbuf->used);
	ubifs_assert(c, len > 0 && wbuf->lnum >= 0 && wbuf->lnum < c->leb_cnt);
	ubifs_assert(c, wbuf->offs >= 0 && wbuf->offs % c->min_io_size == 0);
	ubifs_assert(c, !(wbuf->offs & 7) && wbuf->offs <= c->leb_size);
	ubifs_assert(c, wbuf->avail > 0 && wbuf->avail <= wbuf->size);
	ubifs_assert(c, wbuf->size >= c->min_io_size);
	ubifs_assert(c, wbuf->size <= c->max_write_size);
	ubifs_assert(c, wbuf->size % c->min_io_size == 0);
	ubifs_assert(c, mutex_is_locked(&wbuf->io_mutex));
	ubifs_assert(c, !c->ro_media && !c->ro_mount);
	ubifs_assert(c, !c->space_fixup);
	if (c->leb_size - wbuf->offs >= c->max_write_size)
		ubifs_assert(c, !((wbuf->offs + wbuf->size) % c->max_write_size));

	if (c->leb_size - wbuf->offs - wbuf->used < aligned_len) {
		err = -ENOSPC;
		goto out;
	}

	cancel_wbuf_timer_nolock(wbuf);

	if (c->ro_error)
		return -EROFS;

	if (aligned_len <= wbuf->avail) {
		/*
		 * The node is not very large and fits entirely within
		 * write-buffer.
		 */
		memcpy(wbuf->buf + wbuf->used, buf, len);

		if (aligned_len == wbuf->avail) {
			dbg_io("flush jhead %s wbuf to LEB %d:%d",
			       dbg_jhead(wbuf->jhead), wbuf->lnum, wbuf->offs);
			err = ubifs_leb_write(c, wbuf->lnum, wbuf->buf,
					      wbuf->offs, wbuf->size);
			if (err)
				goto out;

			spin_lock(&wbuf->lock);
			wbuf->offs += wbuf->size;
			if (c->leb_size - wbuf->offs >= c->max_write_size)
				wbuf->size = c->max_write_size;
			else
				wbuf->size = c->leb_size - wbuf->offs;
			wbuf->avail = wbuf->size;
			wbuf->used = 0;
			wbuf->next_ino = 0;
			spin_unlock(&wbuf->lock);
		} else {
			spin_lock(&wbuf->lock);
			wbuf->avail -= aligned_len;
			wbuf->used += aligned_len;
			spin_unlock(&wbuf->lock);
		}

		goto exit;
	}

	written = 0;

	if (wbuf->used) {
		/*
		 * The node is large enough and does not fit entirely within
		 * current available space. We have to fill and flush
		 * write-buffer and switch to the next max. write unit.
		 */
		dbg_io("flush jhead %s wbuf to LEB %d:%d",
		       dbg_jhead(wbuf->jhead), wbuf->lnum, wbuf->offs);
		memcpy(wbuf->buf + wbuf->used, buf, wbuf->avail);
		err = ubifs_leb_write(c, wbuf->lnum, wbuf->buf, wbuf->offs,
				      wbuf->size);
		if (err)
			goto out;

		wbuf->offs += wbuf->size;
		len -= wbuf->avail;
		aligned_len -= wbuf->avail;
		written += wbuf->avail;
	} else if (wbuf->offs & (c->max_write_size - 1)) {
		/*
		 * The write-buffer offset is not aligned to
		 * @c->max_write_size and @wbuf->size is less than
		 * @c->max_write_size. Write @wbuf->size bytes to make sure the
		 * following writes are done in optimal @c->max_write_size
		 * chunks.
		 */
		dbg_io("write %d bytes to LEB %d:%d",
		       wbuf->size, wbuf->lnum, wbuf->offs);
		err = ubifs_leb_write(c, wbuf->lnum, buf, wbuf->offs,
				      wbuf->size);
		if (err)
			goto out;

		wbuf->offs += wbuf->size;
		len -= wbuf->size;
		aligned_len -= wbuf->size;
		written += wbuf->size;
	}

	/*
	 * The remaining data may take more whole max. write units, so write the
	 * remains multiple to max. write unit size directly to the flash media.
	 * We align node length to 8-byte boundary because we anyway flash wbuf
	 * if the remaining space is less than 8 bytes.
	 */
	n = aligned_len >> c->max_write_shift;
	if (n) {
		n <<= c->max_write_shift;
		dbg_io("write %d bytes to LEB %d:%d", n, wbuf->lnum,
		       wbuf->offs);
		err = ubifs_leb_write(c, wbuf->lnum, buf + written,
				      wbuf->offs, n);
		if (err)
			goto out;
		wbuf->offs += n;
		aligned_len -= n;
		len -= n;
		written += n;
	}

	spin_lock(&wbuf->lock);
	if (aligned_len)
		/*
		 * And now we have what's left and what does not take whole
		 * max. write unit, so write it to the write-buffer and we are
		 * done.
		 */
		memcpy(wbuf->buf, buf + written, len);

	if (c->leb_size - wbuf->offs >= c->max_write_size)
		wbuf->size = c->max_write_size;
	else
		wbuf->size = c->leb_size - wbuf->offs;
	wbuf->avail = wbuf->size - aligned_len;
	wbuf->used = aligned_len;
	wbuf->next_ino = 0;
	spin_unlock(&wbuf->lock);

exit:
	if (wbuf->sync_callback) {
		int free = c->leb_size - wbuf->offs - wbuf->used;

		err = wbuf->sync_callback(c, wbuf->lnum, free, 0);
		if (err)
			goto out;
	}

	if (wbuf->used)
		new_wbuf_timer_nolock(c, wbuf);

	return 0;

out:
	ubifs_err(c, "cannot write %d bytes to LEB %d:%d, error %d",
		  len, wbuf->lnum, wbuf->offs, err);
	ubifs_dump_node(c, buf);
	dump_stack();
	ubifs_dump_leb(c, wbuf->lnum);
	return err;
}