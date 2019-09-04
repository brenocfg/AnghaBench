#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_57__   TYPE_9__ ;
typedef  struct TYPE_56__   TYPE_8__ ;
typedef  struct TYPE_55__   TYPE_7__ ;
typedef  struct TYPE_54__   TYPE_6__ ;
typedef  struct TYPE_53__   TYPE_5__ ;
typedef  struct TYPE_52__   TYPE_4__ ;
typedef  struct TYPE_51__   TYPE_3__ ;
typedef  struct TYPE_50__   TYPE_2__ ;
typedef  struct TYPE_49__   TYPE_27__ ;
typedef  struct TYPE_48__   TYPE_1__ ;
typedef  struct TYPE_47__   TYPE_14__ ;
typedef  struct TYPE_46__   TYPE_13__ ;
typedef  struct TYPE_45__   TYPE_12__ ;
typedef  struct TYPE_44__   TYPE_11__ ;
typedef  struct TYPE_43__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct inode {scalar_t__ i_ino; int flags; int i_nlink; int i_size; int i_blocks; int /*<<< orphan*/  i_mode; TYPE_6__* i_mapping; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_sb; void* i_atime; void* i_ctime; void* i_mtime; int /*<<< orphan*/  link_count; int /*<<< orphan*/  sequence_number; scalar_t__ i_generation; scalar_t__ base_mft_record; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct TYPE_57__ {int mft_record_size; int cluster_size; unsigned int cluster_size_bits; int sector_size; unsigned int sector_size_bits; int /*<<< orphan*/  sb; int /*<<< orphan*/  fmask; int /*<<< orphan*/  dmask; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
typedef  TYPE_9__ ntfs_volume ;
struct TYPE_55__ {unsigned int block_size; unsigned int block_clusters; int size; void* block_size_bits; } ;
struct TYPE_50__ {scalar_t__ collation_rule; int block_size; int block_size_bits; int vcn_size; unsigned int vcn_size_bits; } ;
struct TYPE_56__ {TYPE_7__ compressed; TYPE_2__ index; } ;
struct TYPE_49__ {struct inode* rl; } ;
struct TYPE_43__ {int name_len; int initialized_size; int allocated_size; TYPE_8__ itype; int /*<<< orphan*/ * name; void* type; int /*<<< orphan*/  attr_list; scalar_t__ attr_list_size; TYPE_27__ attr_list_rl; scalar_t__ seq_no; } ;
typedef  TYPE_10__ ntfs_inode ;
struct TYPE_44__ {TYPE_14__* attr; scalar_t__ mrec; } ;
typedef  TYPE_11__ ntfs_attr_search_ctx ;
typedef  int loff_t ;
struct TYPE_54__ {int /*<<< orphan*/ * a_ops; } ;
struct TYPE_52__ {int /*<<< orphan*/  value_offset; int /*<<< orphan*/  value_length; } ;
struct TYPE_51__ {int compression_unit; int /*<<< orphan*/  allocated_size; int /*<<< orphan*/  initialized_size; int /*<<< orphan*/  data_size; scalar_t__ lowest_vcn; int /*<<< orphan*/  compressed_size; int /*<<< orphan*/  mapping_pairs_offset; } ;
struct TYPE_53__ {TYPE_4__ resident; TYPE_3__ non_resident; } ;
struct TYPE_48__ {int flags; int /*<<< orphan*/  index_length; } ;
struct TYPE_47__ {int flags; int non_resident; TYPE_5__ data; int /*<<< orphan*/  length; int /*<<< orphan*/  name_offset; scalar_t__ name_length; } ;
struct TYPE_46__ {scalar_t__ type; scalar_t__ collation_rule; TYPE_1__ index; int /*<<< orphan*/  index_block_size; } ;
struct TYPE_45__ {int /*<<< orphan*/  last_access_time; int /*<<< orphan*/  last_mft_change_time; int /*<<< orphan*/  last_data_change_time; } ;
typedef  TYPE_12__ STANDARD_INFORMATION ;
typedef  struct inode MFT_RECORD ;
typedef  TYPE_13__ INDEX_ROOT ;
typedef  TYPE_14__ ATTR_RECORD ;

/* Variables and functions */
 int ATTR_COMPRESSION_MASK ; 
 int ATTR_IS_COMPRESSED ; 
 int ATTR_IS_ENCRYPTED ; 
 int ATTR_IS_SPARSE ; 
 void* AT_ATTRIBUTE_LIST ; 
 int /*<<< orphan*/  AT_BITMAP ; 
 void* AT_DATA ; 
 scalar_t__ AT_FILE_NAME ; 
 void* AT_INDEX_ALLOCATION ; 
 void* AT_INDEX_ROOT ; 
 void* AT_STANDARD_INFORMATION ; 
 int /*<<< orphan*/  CASE_SENSITIVE ; 
 scalar_t__ COLLATION_FILE_NAME ; 
 int EIO ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 scalar_t__ FILE_MFT ; 
 scalar_t__ FILE_Secure ; 
 int /*<<< orphan*/ * I30 ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 scalar_t__ IS_RDONLY (struct inode*) ; 
 int LARGE_INDEX ; 
 int MFT_RECORD_IN_USE ; 
 int MFT_RECORD_IS_DIRECTORY ; 
 scalar_t__ NInoCompressed (TYPE_10__*) ; 
 scalar_t__ NInoEncrypted (TYPE_10__*) ; 
 scalar_t__ NInoMstProtected (TYPE_10__*) ; 
 int /*<<< orphan*/  NInoSetAttrList (TYPE_10__*) ; 
 int /*<<< orphan*/  NInoSetAttrListNonResident (TYPE_10__*) ; 
 int /*<<< orphan*/  NInoSetCompressed (TYPE_10__*) ; 
 int /*<<< orphan*/  NInoSetEncrypted (TYPE_10__*) ; 
 int /*<<< orphan*/  NInoSetIndexAllocPresent (TYPE_10__*) ; 
 int /*<<< orphan*/  NInoSetMstProtected (TYPE_10__*) ; 
 int /*<<< orphan*/  NInoSetNonResident (TYPE_10__*) ; 
 int /*<<< orphan*/  NInoSetSparse (TYPE_10__*) ; 
 scalar_t__ NInoSparse (TYPE_10__*) ; 
 scalar_t__ NTFS_BLOCK_SIZE ; 
 TYPE_10__* NTFS_I (struct inode*) ; 
 TYPE_9__* NTFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVolSetErrors (TYPE_9__*) ; 
 scalar_t__ PAGE_SIZE ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  S_IFDIR ; 
 int /*<<< orphan*/  S_IFREG ; 
 int /*<<< orphan*/  S_IRWXUGO ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_IWUGO ; 
 void* ffs (int) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int load_attribute_list (TYPE_9__*,TYPE_27__*,int /*<<< orphan*/ ,scalar_t__,void*) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 
 struct inode* map_mft_record (TYPE_10__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 void* ntfs2utc (int /*<<< orphan*/ ) ; 
 TYPE_11__* ntfs_attr_get_search_ctx (TYPE_10__*,struct inode*) ; 
 struct inode* ntfs_attr_iget (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int ntfs_attr_lookup (void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_11__*) ; 
 int /*<<< orphan*/  ntfs_attr_put_search_ctx (TYPE_11__*) ; 
 int /*<<< orphan*/  ntfs_attr_reinit_search_ctx (TYPE_11__*) ; 
 scalar_t__ ntfs_attr_size (TYPE_14__*) ; 
 int /*<<< orphan*/  ntfs_compressed_aops ; 
 int /*<<< orphan*/  ntfs_debug (char*,...) ; 
 int /*<<< orphan*/  ntfs_dir_inode_ops ; 
 int /*<<< orphan*/  ntfs_dir_ops ; 
 int /*<<< orphan*/  ntfs_error (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ntfs_file_inode_ops ; 
 int /*<<< orphan*/  ntfs_file_ops ; 
 int /*<<< orphan*/  ntfs_init_big_inode (struct inode*) ; 
 scalar_t__ ntfs_is_extended_system_file (TYPE_11__*) ; 
 int /*<<< orphan*/  ntfs_malloc_nofs (scalar_t__) ; 
 struct inode* ntfs_mapping_pairs_decompress (TYPE_9__*,TYPE_14__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntfs_mst_aops ; 
 int /*<<< orphan*/  ntfs_normal_aops ; 
 int /*<<< orphan*/  ntfs_warning (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 
 void* sle64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unmap_mft_record (TYPE_10__*) ; 

__attribute__((used)) static int ntfs_read_locked_inode(struct inode *vi)
{
	ntfs_volume *vol = NTFS_SB(vi->i_sb);
	ntfs_inode *ni;
	struct inode *bvi;
	MFT_RECORD *m;
	ATTR_RECORD *a;
	STANDARD_INFORMATION *si;
	ntfs_attr_search_ctx *ctx;
	int err = 0;

	ntfs_debug("Entering for i_ino 0x%lx.", vi->i_ino);

	/* Setup the generic vfs inode parts now. */
	vi->i_uid = vol->uid;
	vi->i_gid = vol->gid;
	vi->i_mode = 0;

	/*
	 * Initialize the ntfs specific part of @vi special casing
	 * FILE_MFT which we need to do at mount time.
	 */
	if (vi->i_ino != FILE_MFT)
		ntfs_init_big_inode(vi);
	ni = NTFS_I(vi);

	m = map_mft_record(ni);
	if (IS_ERR(m)) {
		err = PTR_ERR(m);
		goto err_out;
	}
	ctx = ntfs_attr_get_search_ctx(ni, m);
	if (!ctx) {
		err = -ENOMEM;
		goto unm_err_out;
	}

	if (!(m->flags & MFT_RECORD_IN_USE)) {
		ntfs_error(vi->i_sb, "Inode is not in use!");
		goto unm_err_out;
	}
	if (m->base_mft_record) {
		ntfs_error(vi->i_sb, "Inode is an extent inode!");
		goto unm_err_out;
	}

	/* Transfer information from mft record into vfs and ntfs inodes. */
	vi->i_generation = ni->seq_no = le16_to_cpu(m->sequence_number);

	/*
	 * FIXME: Keep in mind that link_count is two for files which have both
	 * a long file name and a short file name as separate entries, so if
	 * we are hiding short file names this will be too high. Either we need
	 * to account for the short file names by subtracting them or we need
	 * to make sure we delete files even though i_nlink is not zero which
	 * might be tricky due to vfs interactions. Need to think about this
	 * some more when implementing the unlink command.
	 */
	set_nlink(vi, le16_to_cpu(m->link_count));
	/*
	 * FIXME: Reparse points can have the directory bit set even though
	 * they would be S_IFLNK. Need to deal with this further below when we
	 * implement reparse points / symbolic links but it will do for now.
	 * Also if not a directory, it could be something else, rather than
	 * a regular file. But again, will do for now.
	 */
	/* Everyone gets all permissions. */
	vi->i_mode |= S_IRWXUGO;
	/* If read-only, no one gets write permissions. */
	if (IS_RDONLY(vi))
		vi->i_mode &= ~S_IWUGO;
	if (m->flags & MFT_RECORD_IS_DIRECTORY) {
		vi->i_mode |= S_IFDIR;
		/*
		 * Apply the directory permissions mask set in the mount
		 * options.
		 */
		vi->i_mode &= ~vol->dmask;
		/* Things break without this kludge! */
		if (vi->i_nlink > 1)
			set_nlink(vi, 1);
	} else {
		vi->i_mode |= S_IFREG;
		/* Apply the file permissions mask set in the mount options. */
		vi->i_mode &= ~vol->fmask;
	}
	/*
	 * Find the standard information attribute in the mft record. At this
	 * stage we haven't setup the attribute list stuff yet, so this could
	 * in fact fail if the standard information is in an extent record, but
	 * I don't think this actually ever happens.
	 */
	err = ntfs_attr_lookup(AT_STANDARD_INFORMATION, NULL, 0, 0, 0, NULL, 0,
			ctx);
	if (unlikely(err)) {
		if (err == -ENOENT) {
			/*
			 * TODO: We should be performing a hot fix here (if the
			 * recover mount option is set) by creating a new
			 * attribute.
			 */
			ntfs_error(vi->i_sb, "$STANDARD_INFORMATION attribute "
					"is missing.");
		}
		goto unm_err_out;
	}
	a = ctx->attr;
	/* Get the standard information attribute value. */
	si = (STANDARD_INFORMATION*)((u8*)a +
			le16_to_cpu(a->data.resident.value_offset));

	/* Transfer information from the standard information into vi. */
	/*
	 * Note: The i_?times do not quite map perfectly onto the NTFS times,
	 * but they are close enough, and in the end it doesn't really matter
	 * that much...
	 */
	/*
	 * mtime is the last change of the data within the file. Not changed
	 * when only metadata is changed, e.g. a rename doesn't affect mtime.
	 */
	vi->i_mtime = ntfs2utc(si->last_data_change_time);
	/*
	 * ctime is the last change of the metadata of the file. This obviously
	 * always changes, when mtime is changed. ctime can be changed on its
	 * own, mtime is then not changed, e.g. when a file is renamed.
	 */
	vi->i_ctime = ntfs2utc(si->last_mft_change_time);
	/*
	 * Last access to the data within the file. Not changed during a rename
	 * for example but changed whenever the file is written to.
	 */
	vi->i_atime = ntfs2utc(si->last_access_time);

	/* Find the attribute list attribute if present. */
	ntfs_attr_reinit_search_ctx(ctx);
	err = ntfs_attr_lookup(AT_ATTRIBUTE_LIST, NULL, 0, 0, 0, NULL, 0, ctx);
	if (err) {
		if (unlikely(err != -ENOENT)) {
			ntfs_error(vi->i_sb, "Failed to lookup attribute list "
					"attribute.");
			goto unm_err_out;
		}
	} else /* if (!err) */ {
		if (vi->i_ino == FILE_MFT)
			goto skip_attr_list_load;
		ntfs_debug("Attribute list found in inode 0x%lx.", vi->i_ino);
		NInoSetAttrList(ni);
		a = ctx->attr;
		if (a->flags & ATTR_COMPRESSION_MASK) {
			ntfs_error(vi->i_sb, "Attribute list attribute is "
					"compressed.");
			goto unm_err_out;
		}
		if (a->flags & ATTR_IS_ENCRYPTED ||
				a->flags & ATTR_IS_SPARSE) {
			if (a->non_resident) {
				ntfs_error(vi->i_sb, "Non-resident attribute "
						"list attribute is encrypted/"
						"sparse.");
				goto unm_err_out;
			}
			ntfs_warning(vi->i_sb, "Resident attribute list "
					"attribute in inode 0x%lx is marked "
					"encrypted/sparse which is not true.  "
					"However, Windows allows this and "
					"chkdsk does not detect or correct it "
					"so we will just ignore the invalid "
					"flags and pretend they are not set.",
					vi->i_ino);
		}
		/* Now allocate memory for the attribute list. */
		ni->attr_list_size = (u32)ntfs_attr_size(a);
		ni->attr_list = ntfs_malloc_nofs(ni->attr_list_size);
		if (!ni->attr_list) {
			ntfs_error(vi->i_sb, "Not enough memory to allocate "
					"buffer for attribute list.");
			err = -ENOMEM;
			goto unm_err_out;
		}
		if (a->non_resident) {
			NInoSetAttrListNonResident(ni);
			if (a->data.non_resident.lowest_vcn) {
				ntfs_error(vi->i_sb, "Attribute list has non "
						"zero lowest_vcn.");
				goto unm_err_out;
			}
			/*
			 * Setup the runlist. No need for locking as we have
			 * exclusive access to the inode at this time.
			 */
			ni->attr_list_rl.rl = ntfs_mapping_pairs_decompress(vol,
					a, NULL);
			if (IS_ERR(ni->attr_list_rl.rl)) {
				err = PTR_ERR(ni->attr_list_rl.rl);
				ni->attr_list_rl.rl = NULL;
				ntfs_error(vi->i_sb, "Mapping pairs "
						"decompression failed.");
				goto unm_err_out;
			}
			/* Now load the attribute list. */
			if ((err = load_attribute_list(vol, &ni->attr_list_rl,
					ni->attr_list, ni->attr_list_size,
					sle64_to_cpu(a->data.non_resident.
					initialized_size)))) {
				ntfs_error(vi->i_sb, "Failed to load "
						"attribute list attribute.");
				goto unm_err_out;
			}
		} else /* if (!a->non_resident) */ {
			if ((u8*)a + le16_to_cpu(a->data.resident.value_offset)
					+ le32_to_cpu(
					a->data.resident.value_length) >
					(u8*)ctx->mrec + vol->mft_record_size) {
				ntfs_error(vi->i_sb, "Corrupt attribute list "
						"in inode.");
				goto unm_err_out;
			}
			/* Now copy the attribute list. */
			memcpy(ni->attr_list, (u8*)a + le16_to_cpu(
					a->data.resident.value_offset),
					le32_to_cpu(
					a->data.resident.value_length));
		}
	}
skip_attr_list_load:
	/*
	 * If an attribute list is present we now have the attribute list value
	 * in ntfs_ino->attr_list and it is ntfs_ino->attr_list_size bytes.
	 */
	if (S_ISDIR(vi->i_mode)) {
		loff_t bvi_size;
		ntfs_inode *bni;
		INDEX_ROOT *ir;
		u8 *ir_end, *index_end;

		/* It is a directory, find index root attribute. */
		ntfs_attr_reinit_search_ctx(ctx);
		err = ntfs_attr_lookup(AT_INDEX_ROOT, I30, 4, CASE_SENSITIVE,
				0, NULL, 0, ctx);
		if (unlikely(err)) {
			if (err == -ENOENT) {
				// FIXME: File is corrupt! Hot-fix with empty
				// index root attribute if recovery option is
				// set.
				ntfs_error(vi->i_sb, "$INDEX_ROOT attribute "
						"is missing.");
			}
			goto unm_err_out;
		}
		a = ctx->attr;
		/* Set up the state. */
		if (unlikely(a->non_resident)) {
			ntfs_error(vol->sb, "$INDEX_ROOT attribute is not "
					"resident.");
			goto unm_err_out;
		}
		/* Ensure the attribute name is placed before the value. */
		if (unlikely(a->name_length && (le16_to_cpu(a->name_offset) >=
				le16_to_cpu(a->data.resident.value_offset)))) {
			ntfs_error(vol->sb, "$INDEX_ROOT attribute name is "
					"placed after the attribute value.");
			goto unm_err_out;
		}
		/*
		 * Compressed/encrypted index root just means that the newly
		 * created files in that directory should be created compressed/
		 * encrypted. However index root cannot be both compressed and
		 * encrypted.
		 */
		if (a->flags & ATTR_COMPRESSION_MASK)
			NInoSetCompressed(ni);
		if (a->flags & ATTR_IS_ENCRYPTED) {
			if (a->flags & ATTR_COMPRESSION_MASK) {
				ntfs_error(vi->i_sb, "Found encrypted and "
						"compressed attribute.");
				goto unm_err_out;
			}
			NInoSetEncrypted(ni);
		}
		if (a->flags & ATTR_IS_SPARSE)
			NInoSetSparse(ni);
		ir = (INDEX_ROOT*)((u8*)a +
				le16_to_cpu(a->data.resident.value_offset));
		ir_end = (u8*)ir + le32_to_cpu(a->data.resident.value_length);
		if (ir_end > (u8*)ctx->mrec + vol->mft_record_size) {
			ntfs_error(vi->i_sb, "$INDEX_ROOT attribute is "
					"corrupt.");
			goto unm_err_out;
		}
		index_end = (u8*)&ir->index +
				le32_to_cpu(ir->index.index_length);
		if (index_end > ir_end) {
			ntfs_error(vi->i_sb, "Directory index is corrupt.");
			goto unm_err_out;
		}
		if (ir->type != AT_FILE_NAME) {
			ntfs_error(vi->i_sb, "Indexed attribute is not "
					"$FILE_NAME.");
			goto unm_err_out;
		}
		if (ir->collation_rule != COLLATION_FILE_NAME) {
			ntfs_error(vi->i_sb, "Index collation rule is not "
					"COLLATION_FILE_NAME.");
			goto unm_err_out;
		}
		ni->itype.index.collation_rule = ir->collation_rule;
		ni->itype.index.block_size = le32_to_cpu(ir->index_block_size);
		if (ni->itype.index.block_size &
				(ni->itype.index.block_size - 1)) {
			ntfs_error(vi->i_sb, "Index block size (%u) is not a "
					"power of two.",
					ni->itype.index.block_size);
			goto unm_err_out;
		}
		if (ni->itype.index.block_size > PAGE_SIZE) {
			ntfs_error(vi->i_sb, "Index block size (%u) > "
					"PAGE_SIZE (%ld) is not "
					"supported.  Sorry.",
					ni->itype.index.block_size,
					PAGE_SIZE);
			err = -EOPNOTSUPP;
			goto unm_err_out;
		}
		if (ni->itype.index.block_size < NTFS_BLOCK_SIZE) {
			ntfs_error(vi->i_sb, "Index block size (%u) < "
					"NTFS_BLOCK_SIZE (%i) is not "
					"supported.  Sorry.",
					ni->itype.index.block_size,
					NTFS_BLOCK_SIZE);
			err = -EOPNOTSUPP;
			goto unm_err_out;
		}
		ni->itype.index.block_size_bits =
				ffs(ni->itype.index.block_size) - 1;
		/* Determine the size of a vcn in the directory index. */
		if (vol->cluster_size <= ni->itype.index.block_size) {
			ni->itype.index.vcn_size = vol->cluster_size;
			ni->itype.index.vcn_size_bits = vol->cluster_size_bits;
		} else {
			ni->itype.index.vcn_size = vol->sector_size;
			ni->itype.index.vcn_size_bits = vol->sector_size_bits;
		}

		/* Setup the index allocation attribute, even if not present. */
		NInoSetMstProtected(ni);
		ni->type = AT_INDEX_ALLOCATION;
		ni->name = I30;
		ni->name_len = 4;

		if (!(ir->index.flags & LARGE_INDEX)) {
			/* No index allocation. */
			vi->i_size = ni->initialized_size =
					ni->allocated_size = 0;
			/* We are done with the mft record, so we release it. */
			ntfs_attr_put_search_ctx(ctx);
			unmap_mft_record(ni);
			m = NULL;
			ctx = NULL;
			goto skip_large_dir_stuff;
		} /* LARGE_INDEX: Index allocation present. Setup state. */
		NInoSetIndexAllocPresent(ni);
		/* Find index allocation attribute. */
		ntfs_attr_reinit_search_ctx(ctx);
		err = ntfs_attr_lookup(AT_INDEX_ALLOCATION, I30, 4,
				CASE_SENSITIVE, 0, NULL, 0, ctx);
		if (unlikely(err)) {
			if (err == -ENOENT)
				ntfs_error(vi->i_sb, "$INDEX_ALLOCATION "
						"attribute is not present but "
						"$INDEX_ROOT indicated it is.");
			else
				ntfs_error(vi->i_sb, "Failed to lookup "
						"$INDEX_ALLOCATION "
						"attribute.");
			goto unm_err_out;
		}
		a = ctx->attr;
		if (!a->non_resident) {
			ntfs_error(vi->i_sb, "$INDEX_ALLOCATION attribute "
					"is resident.");
			goto unm_err_out;
		}
		/*
		 * Ensure the attribute name is placed before the mapping pairs
		 * array.
		 */
		if (unlikely(a->name_length && (le16_to_cpu(a->name_offset) >=
				le16_to_cpu(
				a->data.non_resident.mapping_pairs_offset)))) {
			ntfs_error(vol->sb, "$INDEX_ALLOCATION attribute name "
					"is placed after the mapping pairs "
					"array.");
			goto unm_err_out;
		}
		if (a->flags & ATTR_IS_ENCRYPTED) {
			ntfs_error(vi->i_sb, "$INDEX_ALLOCATION attribute "
					"is encrypted.");
			goto unm_err_out;
		}
		if (a->flags & ATTR_IS_SPARSE) {
			ntfs_error(vi->i_sb, "$INDEX_ALLOCATION attribute "
					"is sparse.");
			goto unm_err_out;
		}
		if (a->flags & ATTR_COMPRESSION_MASK) {
			ntfs_error(vi->i_sb, "$INDEX_ALLOCATION attribute "
					"is compressed.");
			goto unm_err_out;
		}
		if (a->data.non_resident.lowest_vcn) {
			ntfs_error(vi->i_sb, "First extent of "
					"$INDEX_ALLOCATION attribute has non "
					"zero lowest_vcn.");
			goto unm_err_out;
		}
		vi->i_size = sle64_to_cpu(a->data.non_resident.data_size);
		ni->initialized_size = sle64_to_cpu(
				a->data.non_resident.initialized_size);
		ni->allocated_size = sle64_to_cpu(
				a->data.non_resident.allocated_size);
		/*
		 * We are done with the mft record, so we release it. Otherwise
		 * we would deadlock in ntfs_attr_iget().
		 */
		ntfs_attr_put_search_ctx(ctx);
		unmap_mft_record(ni);
		m = NULL;
		ctx = NULL;
		/* Get the index bitmap attribute inode. */
		bvi = ntfs_attr_iget(vi, AT_BITMAP, I30, 4);
		if (IS_ERR(bvi)) {
			ntfs_error(vi->i_sb, "Failed to get bitmap attribute.");
			err = PTR_ERR(bvi);
			goto unm_err_out;
		}
		bni = NTFS_I(bvi);
		if (NInoCompressed(bni) || NInoEncrypted(bni) ||
				NInoSparse(bni)) {
			ntfs_error(vi->i_sb, "$BITMAP attribute is compressed "
					"and/or encrypted and/or sparse.");
			goto iput_unm_err_out;
		}
		/* Consistency check bitmap size vs. index allocation size. */
		bvi_size = i_size_read(bvi);
		if ((bvi_size << 3) < (vi->i_size >>
				ni->itype.index.block_size_bits)) {
			ntfs_error(vi->i_sb, "Index bitmap too small (0x%llx) "
					"for index allocation (0x%llx).",
					bvi_size << 3, vi->i_size);
			goto iput_unm_err_out;
		}
		/* No longer need the bitmap attribute inode. */
		iput(bvi);
skip_large_dir_stuff:
		/* Setup the operations for this inode. */
		vi->i_op = &ntfs_dir_inode_ops;
		vi->i_fop = &ntfs_dir_ops;
		vi->i_mapping->a_ops = &ntfs_mst_aops;
	} else {
		/* It is a file. */
		ntfs_attr_reinit_search_ctx(ctx);

		/* Setup the data attribute, even if not present. */
		ni->type = AT_DATA;
		ni->name = NULL;
		ni->name_len = 0;

		/* Find first extent of the unnamed data attribute. */
		err = ntfs_attr_lookup(AT_DATA, NULL, 0, 0, 0, NULL, 0, ctx);
		if (unlikely(err)) {
			vi->i_size = ni->initialized_size =
					ni->allocated_size = 0;
			if (err != -ENOENT) {
				ntfs_error(vi->i_sb, "Failed to lookup $DATA "
						"attribute.");
				goto unm_err_out;
			}
			/*
			 * FILE_Secure does not have an unnamed $DATA
			 * attribute, so we special case it here.
			 */
			if (vi->i_ino == FILE_Secure)
				goto no_data_attr_special_case;
			/*
			 * Most if not all the system files in the $Extend
			 * system directory do not have unnamed data
			 * attributes so we need to check if the parent
			 * directory of the file is FILE_Extend and if it is
			 * ignore this error. To do this we need to get the
			 * name of this inode from the mft record as the name
			 * contains the back reference to the parent directory.
			 */
			if (ntfs_is_extended_system_file(ctx) > 0)
				goto no_data_attr_special_case;
			// FIXME: File is corrupt! Hot-fix with empty data
			// attribute if recovery option is set.
			ntfs_error(vi->i_sb, "$DATA attribute is missing.");
			goto unm_err_out;
		}
		a = ctx->attr;
		/* Setup the state. */
		if (a->flags & (ATTR_COMPRESSION_MASK | ATTR_IS_SPARSE)) {
			if (a->flags & ATTR_COMPRESSION_MASK) {
				NInoSetCompressed(ni);
				if (vol->cluster_size > 4096) {
					ntfs_error(vi->i_sb, "Found "
							"compressed data but "
							"compression is "
							"disabled due to "
							"cluster size (%i) > "
							"4kiB.",
							vol->cluster_size);
					goto unm_err_out;
				}
				if ((a->flags & ATTR_COMPRESSION_MASK)
						!= ATTR_IS_COMPRESSED) {
					ntfs_error(vi->i_sb, "Found unknown "
							"compression method "
							"or corrupt file.");
					goto unm_err_out;
				}
			}
			if (a->flags & ATTR_IS_SPARSE)
				NInoSetSparse(ni);
		}
		if (a->flags & ATTR_IS_ENCRYPTED) {
			if (NInoCompressed(ni)) {
				ntfs_error(vi->i_sb, "Found encrypted and "
						"compressed data.");
				goto unm_err_out;
			}
			NInoSetEncrypted(ni);
		}
		if (a->non_resident) {
			NInoSetNonResident(ni);
			if (NInoCompressed(ni) || NInoSparse(ni)) {
				if (NInoCompressed(ni) && a->data.non_resident.
						compression_unit != 4) {
					ntfs_error(vi->i_sb, "Found "
							"non-standard "
							"compression unit (%u "
							"instead of 4).  "
							"Cannot handle this.",
							a->data.non_resident.
							compression_unit);
					err = -EOPNOTSUPP;
					goto unm_err_out;
				}
				if (a->data.non_resident.compression_unit) {
					ni->itype.compressed.block_size = 1U <<
							(a->data.non_resident.
							compression_unit +
							vol->cluster_size_bits);
					ni->itype.compressed.block_size_bits =
							ffs(ni->itype.
							compressed.
							block_size) - 1;
					ni->itype.compressed.block_clusters =
							1U << a->data.
							non_resident.
							compression_unit;
				} else {
					ni->itype.compressed.block_size = 0;
					ni->itype.compressed.block_size_bits =
							0;
					ni->itype.compressed.block_clusters =
							0;
				}
				ni->itype.compressed.size = sle64_to_cpu(
						a->data.non_resident.
						compressed_size);
			}
			if (a->data.non_resident.lowest_vcn) {
				ntfs_error(vi->i_sb, "First extent of $DATA "
						"attribute has non zero "
						"lowest_vcn.");
				goto unm_err_out;
			}
			vi->i_size = sle64_to_cpu(
					a->data.non_resident.data_size);
			ni->initialized_size = sle64_to_cpu(
					a->data.non_resident.initialized_size);
			ni->allocated_size = sle64_to_cpu(
					a->data.non_resident.allocated_size);
		} else { /* Resident attribute. */
			vi->i_size = ni->initialized_size = le32_to_cpu(
					a->data.resident.value_length);
			ni->allocated_size = le32_to_cpu(a->length) -
					le16_to_cpu(
					a->data.resident.value_offset);
			if (vi->i_size > ni->allocated_size) {
				ntfs_error(vi->i_sb, "Resident data attribute "
						"is corrupt (size exceeds "
						"allocation).");
				goto unm_err_out;
			}
		}
no_data_attr_special_case:
		/* We are done with the mft record, so we release it. */
		ntfs_attr_put_search_ctx(ctx);
		unmap_mft_record(ni);
		m = NULL;
		ctx = NULL;
		/* Setup the operations for this inode. */
		vi->i_op = &ntfs_file_inode_ops;
		vi->i_fop = &ntfs_file_ops;
		vi->i_mapping->a_ops = &ntfs_normal_aops;
		if (NInoMstProtected(ni))
			vi->i_mapping->a_ops = &ntfs_mst_aops;
		else if (NInoCompressed(ni))
			vi->i_mapping->a_ops = &ntfs_compressed_aops;
	}
	/*
	 * The number of 512-byte blocks used on disk (for stat). This is in so
	 * far inaccurate as it doesn't account for any named streams or other
	 * special non-resident attributes, but that is how Windows works, too,
	 * so we are at least consistent with Windows, if not entirely
	 * consistent with the Linux Way. Doing it the Linux Way would cause a
	 * significant slowdown as it would involve iterating over all
	 * attributes in the mft record and adding the allocated/compressed
	 * sizes of all non-resident attributes present to give us the Linux
	 * correct size that should go into i_blocks (after division by 512).
	 */
	if (S_ISREG(vi->i_mode) && (NInoCompressed(ni) || NInoSparse(ni)))
		vi->i_blocks = ni->itype.compressed.size >> 9;
	else
		vi->i_blocks = ni->allocated_size >> 9;
	ntfs_debug("Done.");
	return 0;
iput_unm_err_out:
	iput(bvi);
unm_err_out:
	if (!err)
		err = -EIO;
	if (ctx)
		ntfs_attr_put_search_ctx(ctx);
	if (m)
		unmap_mft_record(ni);
err_out:
	ntfs_error(vol->sb, "Failed with error code %i.  Marking corrupt "
			"inode 0x%lx as bad.  Run chkdsk.", err, vi->i_ino);
	make_bad_inode(vi);
	if (err != -EOPNOTSUPP && err != -ENOMEM)
		NVolSetErrors(vol);
	return err;
}