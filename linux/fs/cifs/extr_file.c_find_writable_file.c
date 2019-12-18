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
struct cifsInodeInfo {int dummy; } ;
struct cifsFileInfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int cifs_get_writable_file (struct cifsInodeInfo*,int,struct cifsFileInfo**) ; 

struct cifsFileInfo *
find_writable_file(struct cifsInodeInfo *cifs_inode, bool fsuid_only)
{
	struct cifsFileInfo *cfile;
	int rc;

	rc = cifs_get_writable_file(cifs_inode, fsuid_only, &cfile);
	if (rc)
		cifs_dbg(FYI, "couldn't find writable handle rc=%d", rc);

	return cfile;
}