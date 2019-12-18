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
typedef  int /*<<< orphan*/  u64 ;
struct cifs_tcon {int dummy; } ;
struct cifs_sb_info {int /*<<< orphan*/  local_nls; } ;
typedef  int /*<<< orphan*/  FILE_ALL_INFO ;

/* Variables and functions */
 int CIFSGetSrvInodeNumber (unsigned int const,struct cifs_tcon*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_remap (struct cifs_sb_info*) ; 

__attribute__((used)) static int
cifs_get_srv_inum(const unsigned int xid, struct cifs_tcon *tcon,
		  struct cifs_sb_info *cifs_sb, const char *full_path,
		  u64 *uniqueid, FILE_ALL_INFO *data)
{
	/*
	 * We can not use the IndexNumber field by default from Windows or
	 * Samba (in ALL_INFO buf) but we can request it explicitly. The SNIA
	 * CIFS spec claims that this value is unique within the scope of a
	 * share, and the windows docs hint that it's actually unique
	 * per-machine.
	 *
	 * There may be higher info levels that work but are there Windows
	 * server or network appliances for which IndexNumber field is not
	 * guaranteed unique?
	 */
	return CIFSGetSrvInodeNumber(xid, tcon, full_path, uniqueid,
				     cifs_sb->local_nls,
				     cifs_remap(cifs_sb));
}