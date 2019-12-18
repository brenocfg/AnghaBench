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
struct TYPE_2__ {int /*<<< orphan*/  sqnum; } ;
struct ubifs_mst_node {TYPE_1__ ch; int /*<<< orphan*/  flags; } ;
struct ubifs_info {int mst_node_alsz; int leb_size; struct ubifs_mst_node* mst_node; scalar_t__ max_sqnum; struct ubifs_mst_node* rcvrd_mst_node; scalar_t__ ro_mount; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  UBIFS_MST_DIRTY ; 
 scalar_t__ UBIFS_MST_LNUM ; 
 int /*<<< orphan*/  UBIFS_MST_NODE_SZ ; 
 int UBIFS_MST_RCVRY ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_rcvry (char*) ; 
 int get_master_node (struct ubifs_info*,scalar_t__,void**,struct ubifs_mst_node**,void**) ; 
 struct ubifs_mst_node* kmalloc (int const,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ubifs_mst_node*,struct ubifs_mst_node*,int /*<<< orphan*/ ) ; 
 scalar_t__ ubifs_compare_master_node (struct ubifs_info*,struct ubifs_mst_node*,struct ubifs_mst_node*) ; 
 int /*<<< orphan*/  ubifs_dump_node (struct ubifs_info*,struct ubifs_mst_node*) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*) ; 
 int /*<<< orphan*/  ubifs_msg (struct ubifs_info*,char*,scalar_t__) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 int write_rcvrd_mst_node (struct ubifs_info*,struct ubifs_mst_node*) ; 

int ubifs_recover_master_node(struct ubifs_info *c)
{
	void *buf1 = NULL, *buf2 = NULL, *cor1 = NULL, *cor2 = NULL;
	struct ubifs_mst_node *mst1 = NULL, *mst2 = NULL, *mst;
	const int sz = c->mst_node_alsz;
	int err, offs1, offs2;

	dbg_rcvry("recovery");

	err = get_master_node(c, UBIFS_MST_LNUM, &buf1, &mst1, &cor1);
	if (err)
		goto out_free;

	err = get_master_node(c, UBIFS_MST_LNUM + 1, &buf2, &mst2, &cor2);
	if (err)
		goto out_free;

	if (mst1) {
		offs1 = (void *)mst1 - buf1;
		if ((le32_to_cpu(mst1->flags) & UBIFS_MST_RCVRY) &&
		    (offs1 == 0 && !cor1)) {
			/*
			 * mst1 was written by recovery at offset 0 with no
			 * corruption.
			 */
			dbg_rcvry("recovery recovery");
			mst = mst1;
		} else if (mst2) {
			offs2 = (void *)mst2 - buf2;
			if (offs1 == offs2) {
				/* Same offset, so must be the same */
				if (ubifs_compare_master_node(c, mst1, mst2))
					goto out_err;
				mst = mst1;
			} else if (offs2 + sz == offs1) {
				/* 1st LEB was written, 2nd was not */
				if (cor1)
					goto out_err;
				mst = mst1;
			} else if (offs1 == 0 &&
				   c->leb_size - offs2 - sz < sz) {
				/* 1st LEB was unmapped and written, 2nd not */
				if (cor1)
					goto out_err;
				mst = mst1;
			} else
				goto out_err;
		} else {
			/*
			 * 2nd LEB was unmapped and about to be written, so
			 * there must be only one master node in the first LEB
			 * and no corruption.
			 */
			if (offs1 != 0 || cor1)
				goto out_err;
			mst = mst1;
		}
	} else {
		if (!mst2)
			goto out_err;
		/*
		 * 1st LEB was unmapped and about to be written, so there must
		 * be no room left in 2nd LEB.
		 */
		offs2 = (void *)mst2 - buf2;
		if (offs2 + sz + sz <= c->leb_size)
			goto out_err;
		mst = mst2;
	}

	ubifs_msg(c, "recovered master node from LEB %d",
		  (mst == mst1 ? UBIFS_MST_LNUM : UBIFS_MST_LNUM + 1));

	memcpy(c->mst_node, mst, UBIFS_MST_NODE_SZ);

	if (c->ro_mount) {
		/* Read-only mode. Keep a copy for switching to rw mode */
		c->rcvrd_mst_node = kmalloc(sz, GFP_KERNEL);
		if (!c->rcvrd_mst_node) {
			err = -ENOMEM;
			goto out_free;
		}
		memcpy(c->rcvrd_mst_node, c->mst_node, UBIFS_MST_NODE_SZ);

		/*
		 * We had to recover the master node, which means there was an
		 * unclean reboot. However, it is possible that the master node
		 * is clean at this point, i.e., %UBIFS_MST_DIRTY is not set.
		 * E.g., consider the following chain of events:
		 *
		 * 1. UBIFS was cleanly unmounted, so the master node is clean
		 * 2. UBIFS is being mounted R/W and starts changing the master
		 *    node in the first (%UBIFS_MST_LNUM). A power cut happens,
		 *    so this LEB ends up with some amount of garbage at the
		 *    end.
		 * 3. UBIFS is being mounted R/O. We reach this place and
		 *    recover the master node from the second LEB
		 *    (%UBIFS_MST_LNUM + 1). But we cannot update the media
		 *    because we are being mounted R/O. We have to defer the
		 *    operation.
		 * 4. However, this master node (@c->mst_node) is marked as
		 *    clean (since the step 1). And if we just return, the
		 *    mount code will be confused and won't recover the master
		 *    node when it is re-mounter R/W later.
		 *
		 *    Thus, to force the recovery by marking the master node as
		 *    dirty.
		 */
		c->mst_node->flags |= cpu_to_le32(UBIFS_MST_DIRTY);
	} else {
		/* Write the recovered master node */
		c->max_sqnum = le64_to_cpu(mst->ch.sqnum) - 1;
		err = write_rcvrd_mst_node(c, c->mst_node);
		if (err)
			goto out_free;
	}

	vfree(buf2);
	vfree(buf1);

	return 0;

out_err:
	err = -EINVAL;
out_free:
	ubifs_err(c, "failed to recover master node");
	if (mst1) {
		ubifs_err(c, "dumping first master node");
		ubifs_dump_node(c, mst1);
	}
	if (mst2) {
		ubifs_err(c, "dumping second master node");
		ubifs_dump_node(c, mst2);
	}
	vfree(buf2);
	vfree(buf1);
	return err;
}