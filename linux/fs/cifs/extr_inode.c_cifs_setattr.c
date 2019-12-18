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
struct iattr {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct cifs_tcon {scalar_t__ unix_ext; } ;
struct cifs_sb_info {int dummy; } ;

/* Variables and functions */
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 struct cifs_tcon* cifs_sb_master_tcon (struct cifs_sb_info*) ; 
 int cifs_setattr_nounix (struct dentry*,struct iattr*) ; 
 int cifs_setattr_unix (struct dentry*,struct iattr*) ; 

int
cifs_setattr(struct dentry *direntry, struct iattr *attrs)
{
	struct cifs_sb_info *cifs_sb = CIFS_SB(direntry->d_sb);
	struct cifs_tcon *pTcon = cifs_sb_master_tcon(cifs_sb);

	if (pTcon->unix_ext)
		return cifs_setattr_unix(direntry, attrs);

	return cifs_setattr_nounix(direntry, attrs);

	/* BB: add cifs_setattr_legacy for really old servers */
}