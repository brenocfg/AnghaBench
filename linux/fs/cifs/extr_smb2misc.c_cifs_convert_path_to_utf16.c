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
struct cifs_sb_info {int mnt_cifs_flags; int /*<<< orphan*/  local_nls; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {scalar_t__ posix_extensions; } ;

/* Variables and functions */
 int CIFS_MOUNT_MAP_SFM_CHR ; 
 int CIFS_MOUNT_MAP_SPECIAL_CHR ; 
 int NO_MAP_UNI_RSVD ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int SFM_MAP_UNI_RSVD ; 
 int SFU_MAP_UNI_RSVD ; 
 TYPE_1__* cifs_sb_master_tcon (struct cifs_sb_info*) ; 
 scalar_t__ cifs_sb_master_tlink (struct cifs_sb_info*) ; 
 int /*<<< orphan*/ * cifs_strndup_to_utf16 (char const*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 

__le16 *
cifs_convert_path_to_utf16(const char *from, struct cifs_sb_info *cifs_sb)
{
	int len;
	const char *start_of_path;
	__le16 *to;
	int map_type;

	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_MAP_SFM_CHR)
		map_type = SFM_MAP_UNI_RSVD;
	else if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_MAP_SPECIAL_CHR)
		map_type = SFU_MAP_UNI_RSVD;
	else
		map_type = NO_MAP_UNI_RSVD;

	/* Windows doesn't allow paths beginning with \ */
	if (from[0] == '\\')
		start_of_path = from + 1;

	/* SMB311 POSIX extensions paths do not include leading slash */
	else if (cifs_sb_master_tlink(cifs_sb) &&
		 cifs_sb_master_tcon(cifs_sb)->posix_extensions &&
		 (from[0] == '/')) {
		start_of_path = from + 1;
	} else
		start_of_path = from;

	to = cifs_strndup_to_utf16(start_of_path, PATH_MAX, &len,
				   cifs_sb->local_nls, map_type);
	return to;
}