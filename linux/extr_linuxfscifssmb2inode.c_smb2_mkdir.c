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
 int /*<<< orphan*/  CREATE_NOT_FILE ; 
 int /*<<< orphan*/  FILE_CREATE ; 
 int /*<<< orphan*/  FILE_WRITE_ATTRIBUTES ; 
 int /*<<< orphan*/  SMB2_OP_MKDIR ; 
 int smb2_open_op_close (unsigned int const,struct cifs_tcon*,struct cifs_sb_info*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
smb2_mkdir(const unsigned int xid, struct cifs_tcon *tcon, const char *name,
	   struct cifs_sb_info *cifs_sb)
{
	return smb2_open_op_close(xid, tcon, cifs_sb, name,
				  FILE_WRITE_ATTRIBUTES, FILE_CREATE,
				  CREATE_NOT_FILE, NULL, SMB2_OP_MKDIR);
}