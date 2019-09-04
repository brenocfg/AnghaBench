#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int is_valid; int /*<<< orphan*/  fid_mutex; int /*<<< orphan*/  refcount; struct cifs_tcon* tcon; struct cifs_fid* fid; } ;
struct cifs_tcon {TYPE_1__ crfid; } ;
struct cifs_open_parms {int reconnect; struct cifs_fid* fid; int /*<<< orphan*/  disposition; int /*<<< orphan*/  desired_access; scalar_t__ create_options; struct cifs_tcon* tcon; } ;
struct cifs_fid {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_OPEN ; 
 int /*<<< orphan*/  FILE_READ_ATTRIBUTES ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  SMB2_OPLOCK_LEVEL_II ; 
 int SMB2_open (unsigned int,struct cifs_open_parms*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct cifs_fid*,struct cifs_fid*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int open_shroot(unsigned int xid, struct cifs_tcon *tcon, struct cifs_fid *pfid)
{
	struct cifs_open_parms oparams;
	int rc;
	__le16 srch_path = 0; /* Null - since an open of top of share */
	u8 oplock = SMB2_OPLOCK_LEVEL_II;

	mutex_lock(&tcon->crfid.fid_mutex);
	if (tcon->crfid.is_valid) {
		cifs_dbg(FYI, "found a cached root file handle\n");
		memcpy(pfid, tcon->crfid.fid, sizeof(struct cifs_fid));
		kref_get(&tcon->crfid.refcount);
		mutex_unlock(&tcon->crfid.fid_mutex);
		return 0;
	}

	oparams.tcon = tcon;
	oparams.create_options = 0;
	oparams.desired_access = FILE_READ_ATTRIBUTES;
	oparams.disposition = FILE_OPEN;
	oparams.fid = pfid;
	oparams.reconnect = false;

	rc = SMB2_open(xid, &oparams, &srch_path, &oplock, NULL, NULL, NULL);
	if (rc == 0) {
		memcpy(tcon->crfid.fid, pfid, sizeof(struct cifs_fid));
		tcon->crfid.tcon = tcon;
		tcon->crfid.is_valid = true;
		kref_init(&tcon->crfid.refcount);
		kref_get(&tcon->crfid.refcount);
	}
	mutex_unlock(&tcon->crfid.fid_mutex);
	return rc;
}