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
struct ubifs_wbuf {int dummy; } ;
struct ubifs_info {int dummy; } ;
struct bu_info {int cnt; int buf_len; TYPE_1__* zbranch; void* buf; int /*<<< orphan*/  key; int /*<<< orphan*/  gc_seq; } ;
struct TYPE_2__ {int lnum; int offs; int len; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int EAGAIN ; 
 int EBADMSG ; 
 int EINVAL ; 
 int /*<<< orphan*/  dbg_tnck (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dump_stack () ; 
 scalar_t__ maybe_leb_gced (struct ubifs_info*,int,int /*<<< orphan*/ ) ; 
 int read_wbuf (struct ubifs_wbuf*,void*,int,int,int) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,int,int,...) ; 
 struct ubifs_wbuf* ubifs_get_wbuf (struct ubifs_info*,int) ; 
 int ubifs_leb_read (struct ubifs_info*,int,void*,int,int,int /*<<< orphan*/ ) ; 
 int validate_data_node (struct ubifs_info*,void*,TYPE_1__*) ; 

int ubifs_tnc_bulk_read(struct ubifs_info *c, struct bu_info *bu)
{
	int lnum = bu->zbranch[0].lnum, offs = bu->zbranch[0].offs, len, err, i;
	struct ubifs_wbuf *wbuf;
	void *buf;

	len = bu->zbranch[bu->cnt - 1].offs;
	len += bu->zbranch[bu->cnt - 1].len - offs;
	if (len > bu->buf_len) {
		ubifs_err(c, "buffer too small %d vs %d", bu->buf_len, len);
		return -EINVAL;
	}

	/* Do the read */
	wbuf = ubifs_get_wbuf(c, lnum);
	if (wbuf)
		err = read_wbuf(wbuf, bu->buf, len, lnum, offs);
	else
		err = ubifs_leb_read(c, lnum, bu->buf, offs, len, 0);

	/* Check for a race with GC */
	if (maybe_leb_gced(c, lnum, bu->gc_seq))
		return -EAGAIN;

	if (err && err != -EBADMSG) {
		ubifs_err(c, "failed to read from LEB %d:%d, error %d",
			  lnum, offs, err);
		dump_stack();
		dbg_tnck(&bu->key, "key ");
		return err;
	}

	/* Validate the nodes read */
	buf = bu->buf;
	for (i = 0; i < bu->cnt; i++) {
		err = validate_data_node(c, buf, &bu->zbranch[i]);
		if (err)
			return err;
		buf = buf + ALIGN(bu->zbranch[i].len, 8);
	}

	return 0;
}