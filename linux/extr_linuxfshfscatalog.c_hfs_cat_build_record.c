#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct inode {int i_mode; int /*<<< orphan*/  i_sb; } ;
struct hfs_cat_file {int dummy; } ;
struct hfs_cat_dir {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  fdCreator; int /*<<< orphan*/  fdType; } ;
struct TYPE_12__ {int Flags; TYPE_3__ UsrWds; scalar_t__ BkDat; void* MdDat; void* CrDat; void* FlNum; } ;
struct TYPE_9__ {int /*<<< orphan*/  frView; } ;
struct TYPE_10__ {TYPE_1__ UsrInfo; scalar_t__ BkDat; void* MdDat; void* CrDat; void* DirID; } ;
struct TYPE_13__ {TYPE_4__ file; int /*<<< orphan*/  type; TYPE_2__ dir; } ;
typedef  TYPE_5__ hfs_cat_rec ;
typedef  void* __be32 ;
struct TYPE_14__ {int /*<<< orphan*/  s_creator; int /*<<< orphan*/  s_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFS_CDR_DIR ; 
 int /*<<< orphan*/  HFS_CDR_FIL ; 
 int HFS_FIL_LOCK ; 
 int HFS_FIL_THD ; 
 int HFS_FIL_USED ; 
 TYPE_8__* HFS_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int) ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 void* hfs_mtime () ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hfs_cat_build_record(hfs_cat_rec *rec, u32 cnid, struct inode *inode)
{
	__be32 mtime = hfs_mtime();

	memset(rec, 0, sizeof(*rec));
	if (S_ISDIR(inode->i_mode)) {
		rec->type = HFS_CDR_DIR;
		rec->dir.DirID = cpu_to_be32(cnid);
		rec->dir.CrDat = mtime;
		rec->dir.MdDat = mtime;
		rec->dir.BkDat = 0;
		rec->dir.UsrInfo.frView = cpu_to_be16(0xff);
		return sizeof(struct hfs_cat_dir);
	} else {
		/* init some fields for the file record */
		rec->type = HFS_CDR_FIL;
		rec->file.Flags = HFS_FIL_USED | HFS_FIL_THD;
		if (!(inode->i_mode & S_IWUSR))
			rec->file.Flags |= HFS_FIL_LOCK;
		rec->file.FlNum = cpu_to_be32(cnid);
		rec->file.CrDat = mtime;
		rec->file.MdDat = mtime;
		rec->file.BkDat = 0;
		rec->file.UsrWds.fdType = HFS_SB(inode->i_sb)->s_type;
		rec->file.UsrWds.fdCreator = HFS_SB(inode->i_sb)->s_creator;
		return sizeof(struct hfs_cat_file);
	}
}