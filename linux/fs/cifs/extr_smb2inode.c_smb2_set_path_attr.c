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
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_NO_MODE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FILE_OPEN ; 
 int /*<<< orphan*/ * cifs_convert_path_to_utf16 (char const*,struct cifs_sb_info*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int smb2_compound_op (unsigned int const,struct cifs_tcon*,struct cifs_sb_info*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct cifsFileInfo*) ; 

__attribute__((used)) static int
smb2_set_path_attr(const unsigned int xid, struct cifs_tcon *tcon,
		   const char *from_name, const char *to_name,
		   struct cifs_sb_info *cifs_sb, __u32 access, int command,
		   struct cifsFileInfo *cfile)
{
	__le16 *smb2_to_name = NULL;
	int rc;

	smb2_to_name = cifs_convert_path_to_utf16(to_name, cifs_sb);
	if (smb2_to_name == NULL) {
		rc = -ENOMEM;
		goto smb2_rename_path;
	}
	rc = smb2_compound_op(xid, tcon, cifs_sb, from_name, access,
			      FILE_OPEN, 0, ACL_NO_MODE, smb2_to_name,
			      command, cfile);
smb2_rename_path:
	kfree(smb2_to_name);
	return rc;
}