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
struct ubifs_info {int leb_size; int lpt_first; TYPE_1__* ltab; } ;
struct TYPE_2__ {int free; int dirty; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 void* __vmalloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_is_all_ff (void*,int) ; 
 int /*<<< orphan*/  dbg_is_chk_lprops (struct ubifs_info*) ; 
 int dbg_is_node_dirty (struct ubifs_info*,int,int,int) ; 
 int /*<<< orphan*/  dbg_lp (char*,int) ; 
 int get_lpt_node_len (struct ubifs_info*,int) ; 
 int get_lpt_node_type (struct ubifs_info*,void*,int*) ; 
 int get_pad_len (struct ubifs_info*,void*,int) ; 
 int /*<<< orphan*/  is_a_node (struct ubifs_info*,void*,int) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,...) ; 
 int ubifs_leb_read (struct ubifs_info*,int,void*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  vfree (void*) ; 

__attribute__((used)) static int dbg_check_ltab_lnum(struct ubifs_info *c, int lnum)
{
	int err, len = c->leb_size, dirty = 0, node_type, node_num, node_len;
	int ret;
	void *buf, *p;

	if (!dbg_is_chk_lprops(c))
		return 0;

	buf = p = __vmalloc(c->leb_size, GFP_NOFS, PAGE_KERNEL);
	if (!buf) {
		ubifs_err(c, "cannot allocate memory for ltab checking");
		return 0;
	}

	dbg_lp("LEB %d", lnum);

	err = ubifs_leb_read(c, lnum, buf, 0, c->leb_size, 1);
	if (err)
		goto out;

	while (1) {
		if (!is_a_node(c, p, len)) {
			int i, pad_len;

			pad_len = get_pad_len(c, p, len);
			if (pad_len) {
				p += pad_len;
				len -= pad_len;
				dirty += pad_len;
				continue;
			}
			if (!dbg_is_all_ff(p, len)) {
				ubifs_err(c, "invalid empty space in LEB %d at %d",
					  lnum, c->leb_size - len);
				err = -EINVAL;
			}
			i = lnum - c->lpt_first;
			if (len != c->ltab[i].free) {
				ubifs_err(c, "invalid free space in LEB %d (free %d, expected %d)",
					  lnum, len, c->ltab[i].free);
				err = -EINVAL;
			}
			if (dirty != c->ltab[i].dirty) {
				ubifs_err(c, "invalid dirty space in LEB %d (dirty %d, expected %d)",
					  lnum, dirty, c->ltab[i].dirty);
				err = -EINVAL;
			}
			goto out;
		}
		node_type = get_lpt_node_type(c, p, &node_num);
		node_len = get_lpt_node_len(c, node_type);
		ret = dbg_is_node_dirty(c, node_type, lnum, c->leb_size - len);
		if (ret == 1)
			dirty += node_len;
		p += node_len;
		len -= node_len;
	}

	err = 0;
out:
	vfree(buf);
	return err;
}