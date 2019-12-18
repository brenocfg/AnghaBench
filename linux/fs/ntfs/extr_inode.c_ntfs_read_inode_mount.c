#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_46__   TYPE_9__ ;
typedef  struct TYPE_45__   TYPE_8__ ;
typedef  struct TYPE_44__   TYPE_7__ ;
typedef  struct TYPE_43__   TYPE_6__ ;
typedef  struct TYPE_42__   TYPE_5__ ;
typedef  struct TYPE_41__   TYPE_4__ ;
typedef  struct TYPE_40__   TYPE_3__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_25__ ;
typedef  struct TYPE_37__   TYPE_1__ ;
typedef  struct TYPE_36__   TYPE_13__ ;
typedef  struct TYPE_35__   TYPE_12__ ;
typedef  struct TYPE_34__   TYPE_11__ ;
typedef  struct TYPE_33__   TYPE_10__ ;

/* Type definitions */
typedef  char u8 ;
typedef  unsigned int u32 ;
struct super_block {unsigned int s_blocksize; int s_blocksize_bits; } ;
struct inode {int i_generation; scalar_t__ i_ino; int i_size; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; TYPE_3__* i_mapping; struct super_block* i_sb; } ;
struct buffer_head {char* b_data; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  runlist_element ;
struct TYPE_45__ {int mft_record_size; unsigned long long mft_record_size_bits; int mft_lcn; int cluster_size_bits; struct inode* mft_ino; } ;
typedef  TYPE_8__ ntfs_volume ;
struct TYPE_44__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * rl; } ;
struct TYPE_38__ {int /*<<< orphan*/ * rl; } ;
struct TYPE_37__ {int block_size; unsigned long long block_size_bits; } ;
struct TYPE_39__ {TYPE_1__ index; } ;
struct TYPE_46__ {int seq_no; unsigned int attr_list_size; char* attr_list; int initialized_size; int allocated_size; int /*<<< orphan*/  mrec_lock; TYPE_7__ runlist; TYPE_25__ attr_list_rl; TYPE_2__ itype; scalar_t__ name_len; int /*<<< orphan*/ * name; scalar_t__ type; } ;
typedef  TYPE_9__ ntfs_inode ;
struct TYPE_33__ {TYPE_12__* attr; scalar_t__ mrec; } ;
typedef  TYPE_10__ ntfs_attr_search_ctx ;
typedef  int VCN ;
struct TYPE_42__ {scalar_t__ lowest_vcn; scalar_t__ highest_vcn; scalar_t__ allocated_size; scalar_t__ initialized_size; scalar_t__ data_size; } ;
struct TYPE_41__ {scalar_t__ value_length; int /*<<< orphan*/  value_offset; } ;
struct TYPE_43__ {TYPE_5__ non_resident; TYPE_4__ resident; } ;
struct TYPE_40__ {int /*<<< orphan*/ * a_ops; } ;
struct TYPE_36__ {scalar_t__ type; int /*<<< orphan*/  mft_reference; scalar_t__ lowest_vcn; scalar_t__ name_length; int /*<<< orphan*/  length; } ;
struct TYPE_35__ {int flags; TYPE_6__ data; scalar_t__ non_resident; } ;
struct TYPE_34__ {int /*<<< orphan*/  sequence_number; } ;
typedef  int /*<<< orphan*/  NTFS_RECORD ;
typedef  TYPE_11__ MFT_RECORD ;
typedef  TYPE_12__ ATTR_RECORD ;
typedef  TYPE_13__ ATTR_LIST_ENTRY ;

/* Variables and functions */
 int ATTR_COMPRESSION_MASK ; 
 int ATTR_IS_ENCRYPTED ; 
 int ATTR_IS_SPARSE ; 
 scalar_t__ AT_ATTRIBUTE_LIST ; 
 scalar_t__ AT_DATA ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ MREF_LE (int /*<<< orphan*/ ) ; 
 scalar_t__ MSEQNO_LE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NInoSetAttrList (TYPE_9__*) ; 
 int /*<<< orphan*/  NInoSetAttrListNonResident (TYPE_9__*) ; 
 int /*<<< orphan*/  NInoSetMstProtected (TYPE_9__*) ; 
 int /*<<< orphan*/  NInoSetNonResident (TYPE_9__*) ; 
 int /*<<< orphan*/  NInoSetSparseDisabled (TYPE_9__*) ; 
 TYPE_9__* NTFS_I (struct inode*) ; 
 TYPE_8__* NTFS_SB (struct super_block*) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_IFREG ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 
 int load_attribute_list (TYPE_8__*,TYPE_25__*,char*,unsigned int,int) ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  mft_ni_mrec_lock_key ; 
 int /*<<< orphan*/  mft_ni_runlist_lock_key ; 
 TYPE_10__* ntfs_attr_get_search_ctx (TYPE_9__*,TYPE_11__*) ; 
 int ntfs_attr_lookup (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_10__*) ; 
 int /*<<< orphan*/  ntfs_attr_put_search_ctx (TYPE_10__*) ; 
 int /*<<< orphan*/  ntfs_attr_reinit_search_ctx (TYPE_10__*) ; 
 scalar_t__ ntfs_attr_size (TYPE_12__*) ; 
 int /*<<< orphan*/  ntfs_debug (char*,...) ; 
 int /*<<< orphan*/  ntfs_empty_file_ops ; 
 int /*<<< orphan*/  ntfs_empty_inode_ops ; 
 int /*<<< orphan*/  ntfs_error (struct super_block*,char*,...) ; 
 int /*<<< orphan*/  ntfs_free (TYPE_11__*) ; 
 int /*<<< orphan*/  ntfs_init_big_inode (struct inode*) ; 
 char* ntfs_malloc_nofs (unsigned int) ; 
 void* ntfs_mapping_pairs_decompress (TYPE_8__*,TYPE_12__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntfs_mst_aops ; 
 int /*<<< orphan*/  ntfs_read_locked_inode (struct inode*) ; 
 int /*<<< orphan*/  ntfs_warning (struct super_block*,char*) ; 
 scalar_t__ post_read_mst_fixup (int /*<<< orphan*/ *,unsigned int) ; 
 struct buffer_head* sb_bread (struct super_block*,int /*<<< orphan*/ ) ; 
 int sle64_to_cpu (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

int ntfs_read_inode_mount(struct inode *vi)
{
	VCN next_vcn, last_vcn, highest_vcn;
	s64 block;
	struct super_block *sb = vi->i_sb;
	ntfs_volume *vol = NTFS_SB(sb);
	struct buffer_head *bh;
	ntfs_inode *ni;
	MFT_RECORD *m = NULL;
	ATTR_RECORD *a;
	ntfs_attr_search_ctx *ctx;
	unsigned int i, nr_blocks;
	int err;

	ntfs_debug("Entering.");

	/* Initialize the ntfs specific part of @vi. */
	ntfs_init_big_inode(vi);

	ni = NTFS_I(vi);

	/* Setup the data attribute. It is special as it is mst protected. */
	NInoSetNonResident(ni);
	NInoSetMstProtected(ni);
	NInoSetSparseDisabled(ni);
	ni->type = AT_DATA;
	ni->name = NULL;
	ni->name_len = 0;
	/*
	 * This sets up our little cheat allowing us to reuse the async read io
	 * completion handler for directories.
	 */
	ni->itype.index.block_size = vol->mft_record_size;
	ni->itype.index.block_size_bits = vol->mft_record_size_bits;

	/* Very important! Needed to be able to call map_mft_record*(). */
	vol->mft_ino = vi;

	/* Allocate enough memory to read the first mft record. */
	if (vol->mft_record_size > 64 * 1024) {
		ntfs_error(sb, "Unsupported mft record size %i (max 64kiB).",
				vol->mft_record_size);
		goto err_out;
	}
	i = vol->mft_record_size;
	if (i < sb->s_blocksize)
		i = sb->s_blocksize;
	m = (MFT_RECORD*)ntfs_malloc_nofs(i);
	if (!m) {
		ntfs_error(sb, "Failed to allocate buffer for $MFT record 0.");
		goto err_out;
	}

	/* Determine the first block of the $MFT/$DATA attribute. */
	block = vol->mft_lcn << vol->cluster_size_bits >>
			sb->s_blocksize_bits;
	nr_blocks = vol->mft_record_size >> sb->s_blocksize_bits;
	if (!nr_blocks)
		nr_blocks = 1;

	/* Load $MFT/$DATA's first mft record. */
	for (i = 0; i < nr_blocks; i++) {
		bh = sb_bread(sb, block++);
		if (!bh) {
			ntfs_error(sb, "Device read failed.");
			goto err_out;
		}
		memcpy((char*)m + (i << sb->s_blocksize_bits), bh->b_data,
				sb->s_blocksize);
		brelse(bh);
	}

	/* Apply the mst fixups. */
	if (post_read_mst_fixup((NTFS_RECORD*)m, vol->mft_record_size)) {
		/* FIXME: Try to use the $MFTMirr now. */
		ntfs_error(sb, "MST fixup failed. $MFT is corrupt.");
		goto err_out;
	}

	/* Need this to sanity check attribute list references to $MFT. */
	vi->i_generation = ni->seq_no = le16_to_cpu(m->sequence_number);

	/* Provides readpage() for map_mft_record(). */
	vi->i_mapping->a_ops = &ntfs_mst_aops;

	ctx = ntfs_attr_get_search_ctx(ni, m);
	if (!ctx) {
		err = -ENOMEM;
		goto err_out;
	}

	/* Find the attribute list attribute if present. */
	err = ntfs_attr_lookup(AT_ATTRIBUTE_LIST, NULL, 0, 0, 0, NULL, 0, ctx);
	if (err) {
		if (unlikely(err != -ENOENT)) {
			ntfs_error(sb, "Failed to lookup attribute list "
					"attribute. You should run chkdsk.");
			goto put_err_out;
		}
	} else /* if (!err) */ {
		ATTR_LIST_ENTRY *al_entry, *next_al_entry;
		u8 *al_end;
		static const char *es = "  Not allowed.  $MFT is corrupt.  "
				"You should run chkdsk.";

		ntfs_debug("Attribute list attribute found in $MFT.");
		NInoSetAttrList(ni);
		a = ctx->attr;
		if (a->flags & ATTR_COMPRESSION_MASK) {
			ntfs_error(sb, "Attribute list attribute is "
					"compressed.%s", es);
			goto put_err_out;
		}
		if (a->flags & ATTR_IS_ENCRYPTED ||
				a->flags & ATTR_IS_SPARSE) {
			if (a->non_resident) {
				ntfs_error(sb, "Non-resident attribute list "
						"attribute is encrypted/"
						"sparse.%s", es);
				goto put_err_out;
			}
			ntfs_warning(sb, "Resident attribute list attribute "
					"in $MFT system file is marked "
					"encrypted/sparse which is not true.  "
					"However, Windows allows this and "
					"chkdsk does not detect or correct it "
					"so we will just ignore the invalid "
					"flags and pretend they are not set.");
		}
		/* Now allocate memory for the attribute list. */
		ni->attr_list_size = (u32)ntfs_attr_size(a);
		ni->attr_list = ntfs_malloc_nofs(ni->attr_list_size);
		if (!ni->attr_list) {
			ntfs_error(sb, "Not enough memory to allocate buffer "
					"for attribute list.");
			goto put_err_out;
		}
		if (a->non_resident) {
			NInoSetAttrListNonResident(ni);
			if (a->data.non_resident.lowest_vcn) {
				ntfs_error(sb, "Attribute list has non zero "
						"lowest_vcn. $MFT is corrupt. "
						"You should run chkdsk.");
				goto put_err_out;
			}
			/* Setup the runlist. */
			ni->attr_list_rl.rl = ntfs_mapping_pairs_decompress(vol,
					a, NULL);
			if (IS_ERR(ni->attr_list_rl.rl)) {
				err = PTR_ERR(ni->attr_list_rl.rl);
				ni->attr_list_rl.rl = NULL;
				ntfs_error(sb, "Mapping pairs decompression "
						"failed with error code %i.",
						-err);
				goto put_err_out;
			}
			/* Now load the attribute list. */
			if ((err = load_attribute_list(vol, &ni->attr_list_rl,
					ni->attr_list, ni->attr_list_size,
					sle64_to_cpu(a->data.
					non_resident.initialized_size)))) {
				ntfs_error(sb, "Failed to load attribute list "
						"attribute with error code %i.",
						-err);
				goto put_err_out;
			}
		} else /* if (!ctx.attr->non_resident) */ {
			if ((u8*)a + le16_to_cpu(
					a->data.resident.value_offset) +
					le32_to_cpu(
					a->data.resident.value_length) >
					(u8*)ctx->mrec + vol->mft_record_size) {
				ntfs_error(sb, "Corrupt attribute list "
						"attribute.");
				goto put_err_out;
			}
			/* Now copy the attribute list. */
			memcpy(ni->attr_list, (u8*)a + le16_to_cpu(
					a->data.resident.value_offset),
					le32_to_cpu(
					a->data.resident.value_length));
		}
		/* The attribute list is now setup in memory. */
		/*
		 * FIXME: I don't know if this case is actually possible.
		 * According to logic it is not possible but I have seen too
		 * many weird things in MS software to rely on logic... Thus we
		 * perform a manual search and make sure the first $MFT/$DATA
		 * extent is in the base inode. If it is not we abort with an
		 * error and if we ever see a report of this error we will need
		 * to do some magic in order to have the necessary mft record
		 * loaded and in the right place in the page cache. But
		 * hopefully logic will prevail and this never happens...
		 */
		al_entry = (ATTR_LIST_ENTRY*)ni->attr_list;
		al_end = (u8*)al_entry + ni->attr_list_size;
		for (;; al_entry = next_al_entry) {
			/* Out of bounds check. */
			if ((u8*)al_entry < ni->attr_list ||
					(u8*)al_entry > al_end)
				goto em_put_err_out;
			/* Catch the end of the attribute list. */
			if ((u8*)al_entry == al_end)
				goto em_put_err_out;
			if (!al_entry->length)
				goto em_put_err_out;
			if ((u8*)al_entry + 6 > al_end || (u8*)al_entry +
					le16_to_cpu(al_entry->length) > al_end)
				goto em_put_err_out;
			next_al_entry = (ATTR_LIST_ENTRY*)((u8*)al_entry +
					le16_to_cpu(al_entry->length));
			if (le32_to_cpu(al_entry->type) > le32_to_cpu(AT_DATA))
				goto em_put_err_out;
			if (AT_DATA != al_entry->type)
				continue;
			/* We want an unnamed attribute. */
			if (al_entry->name_length)
				goto em_put_err_out;
			/* Want the first entry, i.e. lowest_vcn == 0. */
			if (al_entry->lowest_vcn)
				goto em_put_err_out;
			/* First entry has to be in the base mft record. */
			if (MREF_LE(al_entry->mft_reference) != vi->i_ino) {
				/* MFT references do not match, logic fails. */
				ntfs_error(sb, "BUG: The first $DATA extent "
						"of $MFT is not in the base "
						"mft record. Please report "
						"you saw this message to "
						"linux-ntfs-dev@lists."
						"sourceforge.net");
				goto put_err_out;
			} else {
				/* Sequence numbers must match. */
				if (MSEQNO_LE(al_entry->mft_reference) !=
						ni->seq_no)
					goto em_put_err_out;
				/* Got it. All is ok. We can stop now. */
				break;
			}
		}
	}

	ntfs_attr_reinit_search_ctx(ctx);

	/* Now load all attribute extents. */
	a = NULL;
	next_vcn = last_vcn = highest_vcn = 0;
	while (!(err = ntfs_attr_lookup(AT_DATA, NULL, 0, 0, next_vcn, NULL, 0,
			ctx))) {
		runlist_element *nrl;

		/* Cache the current attribute. */
		a = ctx->attr;
		/* $MFT must be non-resident. */
		if (!a->non_resident) {
			ntfs_error(sb, "$MFT must be non-resident but a "
					"resident extent was found. $MFT is "
					"corrupt. Run chkdsk.");
			goto put_err_out;
		}
		/* $MFT must be uncompressed and unencrypted. */
		if (a->flags & ATTR_COMPRESSION_MASK ||
				a->flags & ATTR_IS_ENCRYPTED ||
				a->flags & ATTR_IS_SPARSE) {
			ntfs_error(sb, "$MFT must be uncompressed, "
					"non-sparse, and unencrypted but a "
					"compressed/sparse/encrypted extent "
					"was found. $MFT is corrupt. Run "
					"chkdsk.");
			goto put_err_out;
		}
		/*
		 * Decompress the mapping pairs array of this extent and merge
		 * the result into the existing runlist. No need for locking
		 * as we have exclusive access to the inode at this time and we
		 * are a mount in progress task, too.
		 */
		nrl = ntfs_mapping_pairs_decompress(vol, a, ni->runlist.rl);
		if (IS_ERR(nrl)) {
			ntfs_error(sb, "ntfs_mapping_pairs_decompress() "
					"failed with error code %ld.  $MFT is "
					"corrupt.", PTR_ERR(nrl));
			goto put_err_out;
		}
		ni->runlist.rl = nrl;

		/* Are we in the first extent? */
		if (!next_vcn) {
			if (a->data.non_resident.lowest_vcn) {
				ntfs_error(sb, "First extent of $DATA "
						"attribute has non zero "
						"lowest_vcn. $MFT is corrupt. "
						"You should run chkdsk.");
				goto put_err_out;
			}
			/* Get the last vcn in the $DATA attribute. */
			last_vcn = sle64_to_cpu(
					a->data.non_resident.allocated_size)
					>> vol->cluster_size_bits;
			/* Fill in the inode size. */
			vi->i_size = sle64_to_cpu(
					a->data.non_resident.data_size);
			ni->initialized_size = sle64_to_cpu(
					a->data.non_resident.initialized_size);
			ni->allocated_size = sle64_to_cpu(
					a->data.non_resident.allocated_size);
			/*
			 * Verify the number of mft records does not exceed
			 * 2^32 - 1.
			 */
			if ((vi->i_size >> vol->mft_record_size_bits) >=
					(1ULL << 32)) {
				ntfs_error(sb, "$MFT is too big! Aborting.");
				goto put_err_out;
			}
			/*
			 * We have got the first extent of the runlist for
			 * $MFT which means it is now relatively safe to call
			 * the normal ntfs_read_inode() function.
			 * Complete reading the inode, this will actually
			 * re-read the mft record for $MFT, this time entering
			 * it into the page cache with which we complete the
			 * kick start of the volume. It should be safe to do
			 * this now as the first extent of $MFT/$DATA is
			 * already known and we would hope that we don't need
			 * further extents in order to find the other
			 * attributes belonging to $MFT. Only time will tell if
			 * this is really the case. If not we will have to play
			 * magic at this point, possibly duplicating a lot of
			 * ntfs_read_inode() at this point. We will need to
			 * ensure we do enough of its work to be able to call
			 * ntfs_read_inode() on extents of $MFT/$DATA. But lets
			 * hope this never happens...
			 */
			ntfs_read_locked_inode(vi);
			if (is_bad_inode(vi)) {
				ntfs_error(sb, "ntfs_read_inode() of $MFT "
						"failed. BUG or corrupt $MFT. "
						"Run chkdsk and if no errors "
						"are found, please report you "
						"saw this message to "
						"linux-ntfs-dev@lists."
						"sourceforge.net");
				ntfs_attr_put_search_ctx(ctx);
				/* Revert to the safe super operations. */
				ntfs_free(m);
				return -1;
			}
			/*
			 * Re-initialize some specifics about $MFT's inode as
			 * ntfs_read_inode() will have set up the default ones.
			 */
			/* Set uid and gid to root. */
			vi->i_uid = GLOBAL_ROOT_UID;
			vi->i_gid = GLOBAL_ROOT_GID;
			/* Regular file. No access for anyone. */
			vi->i_mode = S_IFREG;
			/* No VFS initiated operations allowed for $MFT. */
			vi->i_op = &ntfs_empty_inode_ops;
			vi->i_fop = &ntfs_empty_file_ops;
		}

		/* Get the lowest vcn for the next extent. */
		highest_vcn = sle64_to_cpu(a->data.non_resident.highest_vcn);
		next_vcn = highest_vcn + 1;

		/* Only one extent or error, which we catch below. */
		if (next_vcn <= 0)
			break;

		/* Avoid endless loops due to corruption. */
		if (next_vcn < sle64_to_cpu(
				a->data.non_resident.lowest_vcn)) {
			ntfs_error(sb, "$MFT has corrupt attribute list "
					"attribute. Run chkdsk.");
			goto put_err_out;
		}
	}
	if (err != -ENOENT) {
		ntfs_error(sb, "Failed to lookup $MFT/$DATA attribute extent. "
				"$MFT is corrupt. Run chkdsk.");
		goto put_err_out;
	}
	if (!a) {
		ntfs_error(sb, "$MFT/$DATA attribute not found. $MFT is "
				"corrupt. Run chkdsk.");
		goto put_err_out;
	}
	if (highest_vcn && highest_vcn != last_vcn - 1) {
		ntfs_error(sb, "Failed to load the complete runlist for "
				"$MFT/$DATA. Driver bug or corrupt $MFT. "
				"Run chkdsk.");
		ntfs_debug("highest_vcn = 0x%llx, last_vcn - 1 = 0x%llx",
				(unsigned long long)highest_vcn,
				(unsigned long long)last_vcn - 1);
		goto put_err_out;
	}
	ntfs_attr_put_search_ctx(ctx);
	ntfs_debug("Done.");
	ntfs_free(m);

	/*
	 * Split the locking rules of the MFT inode from the
	 * locking rules of other inodes:
	 */
	lockdep_set_class(&ni->runlist.lock, &mft_ni_runlist_lock_key);
	lockdep_set_class(&ni->mrec_lock, &mft_ni_mrec_lock_key);

	return 0;

em_put_err_out:
	ntfs_error(sb, "Couldn't find first extent of $DATA attribute in "
			"attribute list. $MFT is corrupt. Run chkdsk.");
put_err_out:
	ntfs_attr_put_search_ctx(ctx);
err_out:
	ntfs_error(sb, "Failed. Marking inode as bad.");
	make_bad_inode(vi);
	ntfs_free(m);
	return -1;
}