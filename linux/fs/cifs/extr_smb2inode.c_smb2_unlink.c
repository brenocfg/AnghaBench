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

/* Variables and functions */
 int /*<<< orphan*/  ACL_NO_MODE ; 
 int CREATE_DELETE_ON_CLOSE ; 
 int /*<<< orphan*/  DELETE ; 
 int /*<<< orphan*/  FILE_OPEN ; 
 int OPEN_REPARSE_POINT ; 
 int /*<<< orphan*/  SMB2_OP_DELETE ; 
 int smb2_compound_op (unsigned int const,struct cifs_tcon*,struct cifs_sb_info*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
smb2_unlink(const unsigned int xid, struct cifs_tcon *tcon, const char *name,
	    struct cifs_sb_info *cifs_sb)
{
	return smb2_compound_op(xid, tcon, cifs_sb, name, DELETE, FILE_OPEN,
				CREATE_DELETE_ON_CLOSE | OPEN_REPARSE_POINT,
				ACL_NO_MODE, NULL, SMB2_OP_DELETE, NULL);
}