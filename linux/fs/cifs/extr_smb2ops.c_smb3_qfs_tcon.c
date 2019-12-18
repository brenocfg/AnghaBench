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
typedef  int /*<<< orphan*/  u8 ;
struct cifs_tcon {int nohandlecache; int /*<<< orphan*/  crfid; } ;
struct cifs_open_parms {int reconnect; struct cifs_fid* fid; scalar_t__ create_options; int /*<<< orphan*/  disposition; int /*<<< orphan*/  desired_access; struct cifs_tcon* tcon; } ;
struct cifs_fid {int /*<<< orphan*/  volatile_fid; int /*<<< orphan*/  persistent_fid; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_OPEN ; 
 int /*<<< orphan*/  FILE_READ_ATTRIBUTES ; 
 int /*<<< orphan*/  FS_ATTRIBUTE_INFORMATION ; 
 int /*<<< orphan*/  FS_DEVICE_INFORMATION ; 
 int /*<<< orphan*/  FS_SECTOR_SIZE_INFORMATION ; 
 int /*<<< orphan*/  FS_VOLUME_INFORMATION ; 
 int /*<<< orphan*/  SMB2_OPLOCK_LEVEL_NONE ; 
 int /*<<< orphan*/  SMB2_QFS_attr (unsigned int const,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMB2_close (unsigned int const,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SMB2_open (unsigned int const,struct cifs_open_parms*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SMB3_request_interfaces (unsigned int const,struct cifs_tcon*) ; 
 int /*<<< orphan*/  close_shroot (int /*<<< orphan*/ *) ; 
 int open_shroot (unsigned int const,struct cifs_tcon*,struct cifs_fid*) ; 

__attribute__((used)) static void
smb3_qfs_tcon(const unsigned int xid, struct cifs_tcon *tcon)
{
	int rc;
	__le16 srch_path = 0; /* Null - open root of share */
	u8 oplock = SMB2_OPLOCK_LEVEL_NONE;
	struct cifs_open_parms oparms;
	struct cifs_fid fid;
	bool no_cached_open = tcon->nohandlecache;

	oparms.tcon = tcon;
	oparms.desired_access = FILE_READ_ATTRIBUTES;
	oparms.disposition = FILE_OPEN;
	oparms.create_options = 0;
	oparms.fid = &fid;
	oparms.reconnect = false;

	if (no_cached_open)
		rc = SMB2_open(xid, &oparms, &srch_path, &oplock, NULL, NULL,
			       NULL);
	else
		rc = open_shroot(xid, tcon, &fid);

	if (rc)
		return;

	SMB3_request_interfaces(xid, tcon);

	SMB2_QFS_attr(xid, tcon, fid.persistent_fid, fid.volatile_fid,
			FS_ATTRIBUTE_INFORMATION);
	SMB2_QFS_attr(xid, tcon, fid.persistent_fid, fid.volatile_fid,
			FS_DEVICE_INFORMATION);
	SMB2_QFS_attr(xid, tcon, fid.persistent_fid, fid.volatile_fid,
			FS_VOLUME_INFORMATION);
	SMB2_QFS_attr(xid, tcon, fid.persistent_fid, fid.volatile_fid,
			FS_SECTOR_SIZE_INFORMATION); /* SMB3 specific */
	if (no_cached_open)
		SMB2_close(xid, tcon, fid.persistent_fid, fid.volatile_fid);
	else
		close_shroot(&tcon->crfid);
}