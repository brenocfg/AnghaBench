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
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct cifs_tcon {int Flags; } ;
struct cifs_sb_info {int dummy; } ;

/* Variables and functions */
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int SMB_SHARE_IS_IN_DFS ; 
 char* build_path_from_dentry_optional_prefix (struct dentry*,int) ; 
 struct cifs_tcon* cifs_sb_master_tcon (struct cifs_sb_info*) ; 

char *
build_path_from_dentry(struct dentry *direntry)
{
	struct cifs_sb_info *cifs_sb = CIFS_SB(direntry->d_sb);
	struct cifs_tcon *tcon = cifs_sb_master_tcon(cifs_sb);
	bool prefix = tcon->Flags & SMB_SHARE_IS_IN_DFS;

	return build_path_from_dentry_optional_prefix(direntry,
						      prefix);
}