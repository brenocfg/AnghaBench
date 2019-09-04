#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cifs_sb_info {int dummy; } ;
struct cifs_fattr {void* cf_mtime; void* cf_ctime; void* cf_atime; void* cf_createtime; void* cf_bytes; void* cf_eof; int /*<<< orphan*/  cf_cifsattrs; } ;
struct TYPE_3__ {int /*<<< orphan*/  LastWriteTime; int /*<<< orphan*/  ChangeTime; int /*<<< orphan*/  LastAccessTime; int /*<<< orphan*/  CreationTime; int /*<<< orphan*/  AllocationSize; int /*<<< orphan*/  EndOfFile; int /*<<< orphan*/  ExtFileAttributes; } ;
typedef  TYPE_1__ FILE_DIRECTORY_INFO ;

/* Variables and functions */
 void* cifs_NTtimeToUnix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_fill_common_info (struct cifs_fattr*,struct cifs_sb_info*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cifs_fattr*,int /*<<< orphan*/ ,int) ; 

void
cifs_dir_info_to_fattr(struct cifs_fattr *fattr, FILE_DIRECTORY_INFO *info,
		       struct cifs_sb_info *cifs_sb)
{
	memset(fattr, 0, sizeof(*fattr));
	fattr->cf_cifsattrs = le32_to_cpu(info->ExtFileAttributes);
	fattr->cf_eof = le64_to_cpu(info->EndOfFile);
	fattr->cf_bytes = le64_to_cpu(info->AllocationSize);
	fattr->cf_createtime = le64_to_cpu(info->CreationTime);
	fattr->cf_atime = cifs_NTtimeToUnix(info->LastAccessTime);
	fattr->cf_ctime = cifs_NTtimeToUnix(info->ChangeTime);
	fattr->cf_mtime = cifs_NTtimeToUnix(info->LastWriteTime);

	cifs_fill_common_info(fattr, cifs_sb);
}