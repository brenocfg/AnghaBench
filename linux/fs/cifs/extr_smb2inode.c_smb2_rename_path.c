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
struct cifs_tcon {int dummy; } ;
struct cifs_sb_info {int dummy; } ;
struct cifsFileInfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELETE ; 
 int /*<<< orphan*/  SMB2_OP_RENAME ; 
 int /*<<< orphan*/  cifs_get_writable_path (struct cifs_tcon*,char const*,struct cifsFileInfo**) ; 
 int smb2_set_path_attr (unsigned int const,struct cifs_tcon*,char const*,char const*,struct cifs_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cifsFileInfo*) ; 

int
smb2_rename_path(const unsigned int xid, struct cifs_tcon *tcon,
		 const char *from_name, const char *to_name,
		 struct cifs_sb_info *cifs_sb)
{
	struct cifsFileInfo *cfile;

	cifs_get_writable_path(tcon, from_name, &cfile);

	return smb2_set_path_attr(xid, tcon, from_name, to_name,
				  cifs_sb, DELETE, SMB2_OP_RENAME, cfile);
}