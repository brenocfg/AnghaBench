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
struct ubifs_info {int cmt_orphans; } ;

/* Variables and functions */
 int avail_orphs (struct ubifs_info*) ; 
 int consolidate (struct ubifs_info*) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 int write_orph_nodes (struct ubifs_info*,int) ; 

__attribute__((used)) static int commit_orphans(struct ubifs_info *c)
{
	int avail, atomic = 0, err;

	ubifs_assert(c, c->cmt_orphans > 0);
	avail = avail_orphs(c);
	if (avail < c->cmt_orphans) {
		/* Not enough space to write new orphans, so consolidate */
		err = consolidate(c);
		if (err)
			return err;
		atomic = 1;
	}
	err = write_orph_nodes(c, atomic);
	return err;
}