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
typedef  int u16 ;
struct cifs_dirent {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FYI ; 
#define  SMB_FIND_FILE_BOTH_DIRECTORY_INFO 133 
#define  SMB_FIND_FILE_DIRECTORY_INFO 132 
#define  SMB_FIND_FILE_FULL_DIRECTORY_INFO 131 
#define  SMB_FIND_FILE_ID_FULL_DIR_INFO 130 
#define  SMB_FIND_FILE_INFO_STANDARD 129 
#define  SMB_FIND_FILE_UNIX 128 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cifs_fill_dirent_both (struct cifs_dirent*,void const*) ; 
 int /*<<< orphan*/  cifs_fill_dirent_dir (struct cifs_dirent*,void const*) ; 
 int /*<<< orphan*/  cifs_fill_dirent_full (struct cifs_dirent*,void const*) ; 
 int /*<<< orphan*/  cifs_fill_dirent_search (struct cifs_dirent*,void const*) ; 
 int /*<<< orphan*/  cifs_fill_dirent_std (struct cifs_dirent*,void const*) ; 
 int /*<<< orphan*/  cifs_fill_dirent_unix (struct cifs_dirent*,void const*,int) ; 
 int /*<<< orphan*/  memset (struct cifs_dirent*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cifs_fill_dirent(struct cifs_dirent *de, const void *info,
		u16 level, bool is_unicode)
{
	memset(de, 0, sizeof(*de));

	switch (level) {
	case SMB_FIND_FILE_UNIX:
		cifs_fill_dirent_unix(de, info, is_unicode);
		break;
	case SMB_FIND_FILE_DIRECTORY_INFO:
		cifs_fill_dirent_dir(de, info);
		break;
	case SMB_FIND_FILE_FULL_DIRECTORY_INFO:
		cifs_fill_dirent_full(de, info);
		break;
	case SMB_FIND_FILE_ID_FULL_DIR_INFO:
		cifs_fill_dirent_search(de, info);
		break;
	case SMB_FIND_FILE_BOTH_DIRECTORY_INFO:
		cifs_fill_dirent_both(de, info);
		break;
	case SMB_FIND_FILE_INFO_STANDARD:
		cifs_fill_dirent_std(de, info);
		break;
	default:
		cifs_dbg(FYI, "Unknown findfirst level %d\n", level);
		return -EINVAL;
	}

	return 0;
}