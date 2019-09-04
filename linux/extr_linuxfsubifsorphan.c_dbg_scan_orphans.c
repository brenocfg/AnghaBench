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
struct ubifs_scan_leb {int dummy; } ;
struct ubifs_info {int orph_first; int orph_last; int /*<<< orphan*/  leb_size; scalar_t__ no_orphs; } ;
struct check_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct ubifs_scan_leb*) ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int PTR_ERR (struct ubifs_scan_leb*) ; 
 void* __vmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dbg_read_orphans (struct check_info*,struct ubifs_scan_leb*) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*) ; 
 struct ubifs_scan_leb* ubifs_scan (struct ubifs_info*,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_scan_destroy (struct ubifs_scan_leb*) ; 
 int /*<<< orphan*/  vfree (void*) ; 

__attribute__((used)) static int dbg_scan_orphans(struct ubifs_info *c, struct check_info *ci)
{
	int lnum, err = 0;
	void *buf;

	/* Check no-orphans flag and skip this if no orphans */
	if (c->no_orphs)
		return 0;

	buf = __vmalloc(c->leb_size, GFP_NOFS, PAGE_KERNEL);
	if (!buf) {
		ubifs_err(c, "cannot allocate memory to check orphans");
		return 0;
	}

	for (lnum = c->orph_first; lnum <= c->orph_last; lnum++) {
		struct ubifs_scan_leb *sleb;

		sleb = ubifs_scan(c, lnum, 0, buf, 0);
		if (IS_ERR(sleb)) {
			err = PTR_ERR(sleb);
			break;
		}

		err = dbg_read_orphans(ci, sleb);
		ubifs_scan_destroy(sleb);
		if (err)
			break;
	}

	vfree(buf);
	return err;
}