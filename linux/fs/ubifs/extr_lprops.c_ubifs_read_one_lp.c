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
struct ubifs_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ubifs_lprops const*) ; 
 int PTR_ERR (struct ubifs_lprops const*) ; 
 int /*<<< orphan*/  memcpy (struct ubifs_lprops*,struct ubifs_lprops const*,int) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,int,int) ; 
 int /*<<< orphan*/  ubifs_get_lprops (struct ubifs_info*) ; 
 struct ubifs_lprops* ubifs_lpt_lookup (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  ubifs_release_lprops (struct ubifs_info*) ; 

int ubifs_read_one_lp(struct ubifs_info *c, int lnum, struct ubifs_lprops *lp)
{
	int err = 0;
	const struct ubifs_lprops *lpp;

	ubifs_get_lprops(c);

	lpp = ubifs_lpt_lookup(c, lnum);
	if (IS_ERR(lpp)) {
		err = PTR_ERR(lpp);
		ubifs_err(c, "cannot read properties of LEB %d, error %d",
			  lnum, err);
		goto out;
	}

	memcpy(lp, lpp, sizeof(struct ubifs_lprops));

out:
	ubifs_release_lprops(c);
	return err;
}