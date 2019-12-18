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
struct ubifs_lprops {int dummy; } ;
struct ubifs_info {int lsave_cnt; int* lsave; int leb_cnt; int /*<<< orphan*/  lsave_sz; int /*<<< orphan*/  lsave_offs; int /*<<< orphan*/  lsave_lnum; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct ubifs_lprops*) ; 
 int PTR_ERR (struct ubifs_lprops*) ; 
 int ubifs_leb_read (struct ubifs_info*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ubifs_lprops* ubifs_lpt_lookup (struct ubifs_info*,int) ; 
 int unpack_lsave (struct ubifs_info*,void*) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 void* vmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_lsave(struct ubifs_info *c)
{
	int err, i;
	void *buf;

	buf = vmalloc(c->lsave_sz);
	if (!buf)
		return -ENOMEM;
	err = ubifs_leb_read(c, c->lsave_lnum, buf, c->lsave_offs,
			     c->lsave_sz, 1);
	if (err)
		goto out;
	err = unpack_lsave(c, buf);
	if (err)
		goto out;
	for (i = 0; i < c->lsave_cnt; i++) {
		int lnum = c->lsave[i];
		struct ubifs_lprops *lprops;

		/*
		 * Due to automatic resizing, the values in the lsave table
		 * could be beyond the volume size - just ignore them.
		 */
		if (lnum >= c->leb_cnt)
			continue;
		lprops = ubifs_lpt_lookup(c, lnum);
		if (IS_ERR(lprops)) {
			err = PTR_ERR(lprops);
			goto out;
		}
	}
out:
	vfree(buf);
	return err;
}