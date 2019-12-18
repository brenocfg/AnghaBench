#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_12__ {void* tagIdent; } ;
struct unallocSpaceEntry {TYPE_1__ descTag; void* lengthAllocDescs; } ;
struct udf_sb_info {int s_udfrev; int s_serial_number; } ;
struct TYPE_18__ {int logicalBlockNum; } ;
struct TYPE_13__ {int /*<<< orphan*/  i_data; } ;
struct udf_inode_info {int i_lenAlloc; int i_extraPerms; int i_alloc_type; scalar_t__ i_efe; int i_unique; int i_lenEAttr; int i_checkpoint; int i_lenStreams; TYPE_9__ i_location; scalar_t__ i_use; scalar_t__ i_strat4096; int /*<<< orphan*/  i_crtime; int /*<<< orphan*/  i_locStreamdir; scalar_t__ i_streamdir; TYPE_2__ i_ext; } ;
struct tag {int dummy; } ;
struct regid {void** identSuffix; int /*<<< orphan*/  ident; } ;
struct long_ad {void* extLength; int /*<<< orphan*/  extLocation; } ;
struct inode {int i_mode; scalar_t__ i_nlink; int i_size; int i_blocks; int /*<<< orphan*/  i_ino; TYPE_5__* i_sb; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; } ;
struct TYPE_17__ {int /*<<< orphan*/  tagChecksum; void* descCRC; void* descCRCLength; void* tagLocation; void* tagSerialNum; void* descVersion; void* tagIdent; } ;
struct TYPE_15__ {void* flags; int /*<<< orphan*/  fileType; void* numEntries; void* strategyType; void* strategyParameter; } ;
struct fileEntry {TYPE_7__ descTag; TYPE_4__ icbTag; void* checkpoint; void* lengthAllocDescs; void* lengthExtendedAttr; void* uniqueID; struct regid impIdent; int /*<<< orphan*/  attrTime; int /*<<< orphan*/  modificationTime; int /*<<< orphan*/  accessTime; void* logicalBlocksRecorded; void* informationLength; void* fileLinkCount; void* permissions; void* gid; void* uid; } ;
struct TYPE_14__ {void* tagIdent; } ;
struct extendedFileEntry {TYPE_3__ descTag; void* checkpoint; void* lengthAllocDescs; void* lengthExtendedAttr; void* uniqueID; struct regid impIdent; int /*<<< orphan*/  attrTime; int /*<<< orphan*/  createTime; int /*<<< orphan*/  modificationTime; int /*<<< orphan*/  accessTime; struct long_ad streamDirectoryICB; void* logicalBlocksRecorded; void* objectSize; } ;
struct deviceSpec {int attrSubtype; void* minorDeviceIdent; void* majorDeviceIdent; scalar_t__ impUse; void* impUseLength; void* attrLength; void* attrType; } ;
struct buffer_head {struct regid* b_data; } ;
struct TYPE_16__ {unsigned char s_blocksize_bits; int s_blocksize; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ICBTAG_FILE_TYPE_BLOCK ; 
 int /*<<< orphan*/  ICBTAG_FILE_TYPE_CHAR ; 
 int /*<<< orphan*/  ICBTAG_FILE_TYPE_DIRECTORY ; 
 int /*<<< orphan*/  ICBTAG_FILE_TYPE_FIFO ; 
 int /*<<< orphan*/  ICBTAG_FILE_TYPE_REGULAR ; 
 int /*<<< orphan*/  ICBTAG_FILE_TYPE_SOCKET ; 
 int /*<<< orphan*/  ICBTAG_FILE_TYPE_SYMLINK ; 
 int /*<<< orphan*/  ICBTAG_FILE_TYPE_USE ; 
 int ICBTAG_FLAG_AD_IN_ICB ; 
 int ICBTAG_FLAG_AD_MASK ; 
 int ICBTAG_FLAG_SETGID ; 
 int ICBTAG_FLAG_SETUID ; 
 int ICBTAG_FLAG_STICKY ; 
 scalar_t__ S_ISBLK (int) ; 
 scalar_t__ S_ISCHR (int) ; 
 scalar_t__ S_ISDIR (int) ; 
 scalar_t__ S_ISFIFO (int) ; 
 int S_ISGID ; 
 scalar_t__ S_ISLNK (int) ; 
 scalar_t__ S_ISREG (int) ; 
 scalar_t__ S_ISSOCK (int) ; 
 int S_ISUID ; 
 int S_ISVTX ; 
 int TAG_IDENT_EFE ; 
 int TAG_IDENT_FE ; 
 int TAG_IDENT_USE ; 
 int /*<<< orphan*/  UDF_FLAG_GID_FORGET ; 
 int /*<<< orphan*/  UDF_FLAG_UID_FORGET ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  UDF_ID_DEVELOPER ; 
 int UDF_INVALID_ID ; 
 void* UDF_OS_CLASS_UNIX ; 
 void* UDF_OS_ID_LINUX ; 
 scalar_t__ UDF_QUERY_FLAG (TYPE_5__*,int /*<<< orphan*/ ) ; 
 struct udf_sb_info* UDF_SB (TYPE_5__*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ buffer_write_io_error (struct buffer_head*) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 void* cpu_to_le64 (int) ; 
 int /*<<< orphan*/  cpu_to_lelb (int /*<<< orphan*/ ) ; 
 int crc_itu_t (int /*<<< orphan*/ ,char*,int) ; 
 int i_gid_read (struct inode*) ; 
 int i_uid_read (struct inode*) ; 
 int imajor (struct inode*) ; 
 int iminor (struct inode*) ; 
 int le16_to_cpu (void*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  memcpy (struct regid*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct regid*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_dirty_buffer (struct buffer_head*) ; 
 scalar_t__ udf_add_extendedattr (struct inode*,int,int,int) ; 
 int /*<<< orphan*/  udf_adjust_time (struct udf_inode_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_debug (char*) ; 
 scalar_t__ udf_get_extendedattr (struct inode*,int,int) ; 
 int /*<<< orphan*/  udf_get_lb_pblock (TYPE_5__*,TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_tag_checksum (TYPE_7__*) ; 
 struct buffer_head* udf_tgetblk (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_time_to_disk_stamp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_warn (TYPE_5__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

__attribute__((used)) static int udf_update_inode(struct inode *inode, int do_sync)
{
	struct buffer_head *bh = NULL;
	struct fileEntry *fe;
	struct extendedFileEntry *efe;
	uint64_t lb_recorded;
	uint32_t udfperms;
	uint16_t icbflags;
	uint16_t crclen;
	int err = 0;
	struct udf_sb_info *sbi = UDF_SB(inode->i_sb);
	unsigned char blocksize_bits = inode->i_sb->s_blocksize_bits;
	struct udf_inode_info *iinfo = UDF_I(inode);

	bh = udf_tgetblk(inode->i_sb,
			udf_get_lb_pblock(inode->i_sb, &iinfo->i_location, 0));
	if (!bh) {
		udf_debug("getblk failure\n");
		return -EIO;
	}

	lock_buffer(bh);
	memset(bh->b_data, 0, inode->i_sb->s_blocksize);
	fe = (struct fileEntry *)bh->b_data;
	efe = (struct extendedFileEntry *)bh->b_data;

	if (iinfo->i_use) {
		struct unallocSpaceEntry *use =
			(struct unallocSpaceEntry *)bh->b_data;

		use->lengthAllocDescs = cpu_to_le32(iinfo->i_lenAlloc);
		memcpy(bh->b_data + sizeof(struct unallocSpaceEntry),
		       iinfo->i_ext.i_data, inode->i_sb->s_blocksize -
					sizeof(struct unallocSpaceEntry));
		use->descTag.tagIdent = cpu_to_le16(TAG_IDENT_USE);
		crclen = sizeof(struct unallocSpaceEntry);

		goto finish;
	}

	if (UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_UID_FORGET))
		fe->uid = cpu_to_le32(UDF_INVALID_ID);
	else
		fe->uid = cpu_to_le32(i_uid_read(inode));

	if (UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_GID_FORGET))
		fe->gid = cpu_to_le32(UDF_INVALID_ID);
	else
		fe->gid = cpu_to_le32(i_gid_read(inode));

	udfperms = ((inode->i_mode & 0007)) |
		   ((inode->i_mode & 0070) << 2) |
		   ((inode->i_mode & 0700) << 4);

	udfperms |= iinfo->i_extraPerms;
	fe->permissions = cpu_to_le32(udfperms);

	if (S_ISDIR(inode->i_mode) && inode->i_nlink > 0)
		fe->fileLinkCount = cpu_to_le16(inode->i_nlink - 1);
	else
		fe->fileLinkCount = cpu_to_le16(inode->i_nlink);

	fe->informationLength = cpu_to_le64(inode->i_size);

	if (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode)) {
		struct regid *eid;
		struct deviceSpec *dsea =
			(struct deviceSpec *)udf_get_extendedattr(inode, 12, 1);
		if (!dsea) {
			dsea = (struct deviceSpec *)
				udf_add_extendedattr(inode,
						     sizeof(struct deviceSpec) +
						     sizeof(struct regid), 12, 0x3);
			dsea->attrType = cpu_to_le32(12);
			dsea->attrSubtype = 1;
			dsea->attrLength = cpu_to_le32(
						sizeof(struct deviceSpec) +
						sizeof(struct regid));
			dsea->impUseLength = cpu_to_le32(sizeof(struct regid));
		}
		eid = (struct regid *)dsea->impUse;
		memset(eid, 0, sizeof(*eid));
		strcpy(eid->ident, UDF_ID_DEVELOPER);
		eid->identSuffix[0] = UDF_OS_CLASS_UNIX;
		eid->identSuffix[1] = UDF_OS_ID_LINUX;
		dsea->majorDeviceIdent = cpu_to_le32(imajor(inode));
		dsea->minorDeviceIdent = cpu_to_le32(iminor(inode));
	}

	if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB)
		lb_recorded = 0; /* No extents => no blocks! */
	else
		lb_recorded =
			(inode->i_blocks + (1 << (blocksize_bits - 9)) - 1) >>
			(blocksize_bits - 9);

	if (iinfo->i_efe == 0) {
		memcpy(bh->b_data + sizeof(struct fileEntry),
		       iinfo->i_ext.i_data,
		       inode->i_sb->s_blocksize - sizeof(struct fileEntry));
		fe->logicalBlocksRecorded = cpu_to_le64(lb_recorded);

		udf_time_to_disk_stamp(&fe->accessTime, inode->i_atime);
		udf_time_to_disk_stamp(&fe->modificationTime, inode->i_mtime);
		udf_time_to_disk_stamp(&fe->attrTime, inode->i_ctime);
		memset(&(fe->impIdent), 0, sizeof(struct regid));
		strcpy(fe->impIdent.ident, UDF_ID_DEVELOPER);
		fe->impIdent.identSuffix[0] = UDF_OS_CLASS_UNIX;
		fe->impIdent.identSuffix[1] = UDF_OS_ID_LINUX;
		fe->uniqueID = cpu_to_le64(iinfo->i_unique);
		fe->lengthExtendedAttr = cpu_to_le32(iinfo->i_lenEAttr);
		fe->lengthAllocDescs = cpu_to_le32(iinfo->i_lenAlloc);
		fe->checkpoint = cpu_to_le32(iinfo->i_checkpoint);
		fe->descTag.tagIdent = cpu_to_le16(TAG_IDENT_FE);
		crclen = sizeof(struct fileEntry);
	} else {
		memcpy(bh->b_data + sizeof(struct extendedFileEntry),
		       iinfo->i_ext.i_data,
		       inode->i_sb->s_blocksize -
					sizeof(struct extendedFileEntry));
		efe->objectSize =
			cpu_to_le64(inode->i_size + iinfo->i_lenStreams);
		efe->logicalBlocksRecorded = cpu_to_le64(lb_recorded);

		if (iinfo->i_streamdir) {
			struct long_ad *icb_lad = &efe->streamDirectoryICB;

			icb_lad->extLocation =
				cpu_to_lelb(iinfo->i_locStreamdir);
			icb_lad->extLength =
				cpu_to_le32(inode->i_sb->s_blocksize);
		}

		udf_adjust_time(iinfo, inode->i_atime);
		udf_adjust_time(iinfo, inode->i_mtime);
		udf_adjust_time(iinfo, inode->i_ctime);

		udf_time_to_disk_stamp(&efe->accessTime, inode->i_atime);
		udf_time_to_disk_stamp(&efe->modificationTime, inode->i_mtime);
		udf_time_to_disk_stamp(&efe->createTime, iinfo->i_crtime);
		udf_time_to_disk_stamp(&efe->attrTime, inode->i_ctime);

		memset(&(efe->impIdent), 0, sizeof(efe->impIdent));
		strcpy(efe->impIdent.ident, UDF_ID_DEVELOPER);
		efe->impIdent.identSuffix[0] = UDF_OS_CLASS_UNIX;
		efe->impIdent.identSuffix[1] = UDF_OS_ID_LINUX;
		efe->uniqueID = cpu_to_le64(iinfo->i_unique);
		efe->lengthExtendedAttr = cpu_to_le32(iinfo->i_lenEAttr);
		efe->lengthAllocDescs = cpu_to_le32(iinfo->i_lenAlloc);
		efe->checkpoint = cpu_to_le32(iinfo->i_checkpoint);
		efe->descTag.tagIdent = cpu_to_le16(TAG_IDENT_EFE);
		crclen = sizeof(struct extendedFileEntry);
	}

finish:
	if (iinfo->i_strat4096) {
		fe->icbTag.strategyType = cpu_to_le16(4096);
		fe->icbTag.strategyParameter = cpu_to_le16(1);
		fe->icbTag.numEntries = cpu_to_le16(2);
	} else {
		fe->icbTag.strategyType = cpu_to_le16(4);
		fe->icbTag.numEntries = cpu_to_le16(1);
	}

	if (iinfo->i_use)
		fe->icbTag.fileType = ICBTAG_FILE_TYPE_USE;
	else if (S_ISDIR(inode->i_mode))
		fe->icbTag.fileType = ICBTAG_FILE_TYPE_DIRECTORY;
	else if (S_ISREG(inode->i_mode))
		fe->icbTag.fileType = ICBTAG_FILE_TYPE_REGULAR;
	else if (S_ISLNK(inode->i_mode))
		fe->icbTag.fileType = ICBTAG_FILE_TYPE_SYMLINK;
	else if (S_ISBLK(inode->i_mode))
		fe->icbTag.fileType = ICBTAG_FILE_TYPE_BLOCK;
	else if (S_ISCHR(inode->i_mode))
		fe->icbTag.fileType = ICBTAG_FILE_TYPE_CHAR;
	else if (S_ISFIFO(inode->i_mode))
		fe->icbTag.fileType = ICBTAG_FILE_TYPE_FIFO;
	else if (S_ISSOCK(inode->i_mode))
		fe->icbTag.fileType = ICBTAG_FILE_TYPE_SOCKET;

	icbflags =	iinfo->i_alloc_type |
			((inode->i_mode & S_ISUID) ? ICBTAG_FLAG_SETUID : 0) |
			((inode->i_mode & S_ISGID) ? ICBTAG_FLAG_SETGID : 0) |
			((inode->i_mode & S_ISVTX) ? ICBTAG_FLAG_STICKY : 0) |
			(le16_to_cpu(fe->icbTag.flags) &
				~(ICBTAG_FLAG_AD_MASK | ICBTAG_FLAG_SETUID |
				ICBTAG_FLAG_SETGID | ICBTAG_FLAG_STICKY));

	fe->icbTag.flags = cpu_to_le16(icbflags);
	if (sbi->s_udfrev >= 0x0200)
		fe->descTag.descVersion = cpu_to_le16(3);
	else
		fe->descTag.descVersion = cpu_to_le16(2);
	fe->descTag.tagSerialNum = cpu_to_le16(sbi->s_serial_number);
	fe->descTag.tagLocation = cpu_to_le32(
					iinfo->i_location.logicalBlockNum);
	crclen += iinfo->i_lenEAttr + iinfo->i_lenAlloc - sizeof(struct tag);
	fe->descTag.descCRCLength = cpu_to_le16(crclen);
	fe->descTag.descCRC = cpu_to_le16(crc_itu_t(0, (char *)fe + sizeof(struct tag),
						  crclen));
	fe->descTag.tagChecksum = udf_tag_checksum(&fe->descTag);

	set_buffer_uptodate(bh);
	unlock_buffer(bh);

	/* write the data blocks */
	mark_buffer_dirty(bh);
	if (do_sync) {
		sync_dirty_buffer(bh);
		if (buffer_write_io_error(bh)) {
			udf_warn(inode->i_sb, "IO error syncing udf inode [%08lx]\n",
				 inode->i_ino);
			err = -EIO;
		}
	}
	brelse(bh);

	return err;
}