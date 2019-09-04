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
struct cifs_sb_info {int mnt_cifs_flags; } ;

/* Variables and functions */
 int CIFS_MOUNT_MAP_SFM_CHR ; 
 int CIFS_MOUNT_MAP_SPECIAL_CHR ; 
 int NO_MAP_UNI_RSVD ; 
 int SFM_MAP_UNI_RSVD ; 
 int SFU_MAP_UNI_RSVD ; 

int cifs_remap(struct cifs_sb_info *cifs_sb)
{
	int map_type;

	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_MAP_SFM_CHR)
		map_type = SFM_MAP_UNI_RSVD;
	else if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_MAP_SPECIAL_CHR)
		map_type = SFU_MAP_UNI_RSVD;
	else
		map_type = NO_MAP_UNI_RSVD;

	return map_type;
}