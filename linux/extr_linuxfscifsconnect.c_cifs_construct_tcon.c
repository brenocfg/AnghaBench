#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct smb_vol {int no_linux_ext; int /*<<< orphan*/  password; struct smb_vol* username; int /*<<< orphan*/  sign; int /*<<< orphan*/  sectype; int /*<<< orphan*/  local_lease; int /*<<< orphan*/  nohandlecache; int /*<<< orphan*/  nocase; int /*<<< orphan*/  retry; int /*<<< orphan*/  UNC; void* cred_uid; void* linux_uid; int /*<<< orphan*/  local_nls; } ;
struct cifs_tcon {scalar_t__ posix_extensions; TYPE_1__* ses; int /*<<< orphan*/  unix_ext; int /*<<< orphan*/  local_lease; int /*<<< orphan*/  nohandlecache; int /*<<< orphan*/  nocase; int /*<<< orphan*/  retry; int /*<<< orphan*/  treeName; } ;
struct cifs_ses {scalar_t__ posix_extensions; TYPE_1__* ses; int /*<<< orphan*/  unix_ext; int /*<<< orphan*/  local_lease; int /*<<< orphan*/  nohandlecache; int /*<<< orphan*/  nocase; int /*<<< orphan*/  retry; int /*<<< orphan*/  treeName; } ;
struct cifs_sb_info {int /*<<< orphan*/  mnt_cifs_flags; int /*<<< orphan*/  local_nls; } ;
typedef  void* kuid_t ;
struct TYPE_5__ {int /*<<< orphan*/  srv_count; } ;
struct TYPE_4__ {TYPE_2__* server; int /*<<< orphan*/  sign; int /*<<< orphan*/  sectype; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_MOUNT_POSIX_PATHS ; 
 int ENOMEM ; 
 struct cifs_tcon* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct cifs_tcon*) ; 
 scalar_t__ cap_unix (struct cifs_tcon*) ; 
 struct cifs_tcon* cifs_get_smb_ses (TYPE_2__*,struct smb_vol*) ; 
 struct cifs_tcon* cifs_get_tcon (struct cifs_tcon*,struct smb_vol*) ; 
 int /*<<< orphan*/  cifs_put_smb_ses (struct cifs_tcon*) ; 
 int /*<<< orphan*/  cifs_put_tcp_session (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct cifs_tcon* cifs_sb_master_tcon (struct cifs_sb_info*) ; 
 int cifs_set_vol_auth (struct smb_vol*,TYPE_1__*) ; 
 int /*<<< orphan*/  cifs_tcp_ses_lock ; 
 int /*<<< orphan*/  kfree (struct smb_vol*) ; 
 struct smb_vol* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_cifs_unix_caps (int /*<<< orphan*/ ,struct cifs_tcon*,int /*<<< orphan*/ *,struct smb_vol*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct cifs_tcon *
cifs_construct_tcon(struct cifs_sb_info *cifs_sb, kuid_t fsuid)
{
	int rc;
	struct cifs_tcon *master_tcon = cifs_sb_master_tcon(cifs_sb);
	struct cifs_ses *ses;
	struct cifs_tcon *tcon = NULL;
	struct smb_vol *vol_info;

	vol_info = kzalloc(sizeof(*vol_info), GFP_KERNEL);
	if (vol_info == NULL)
		return ERR_PTR(-ENOMEM);

	vol_info->local_nls = cifs_sb->local_nls;
	vol_info->linux_uid = fsuid;
	vol_info->cred_uid = fsuid;
	vol_info->UNC = master_tcon->treeName;
	vol_info->retry = master_tcon->retry;
	vol_info->nocase = master_tcon->nocase;
	vol_info->nohandlecache = master_tcon->nohandlecache;
	vol_info->local_lease = master_tcon->local_lease;
	vol_info->no_linux_ext = !master_tcon->unix_ext;
	vol_info->sectype = master_tcon->ses->sectype;
	vol_info->sign = master_tcon->ses->sign;

	rc = cifs_set_vol_auth(vol_info, master_tcon->ses);
	if (rc) {
		tcon = ERR_PTR(rc);
		goto out;
	}

	/* get a reference for the same TCP session */
	spin_lock(&cifs_tcp_ses_lock);
	++master_tcon->ses->server->srv_count;
	spin_unlock(&cifs_tcp_ses_lock);

	ses = cifs_get_smb_ses(master_tcon->ses->server, vol_info);
	if (IS_ERR(ses)) {
		tcon = (struct cifs_tcon *)ses;
		cifs_put_tcp_session(master_tcon->ses->server, 0);
		goto out;
	}

	tcon = cifs_get_tcon(ses, vol_info);
	if (IS_ERR(tcon)) {
		cifs_put_smb_ses(ses);
		goto out;
	}

	/* if new SMB3.11 POSIX extensions are supported do not remap / and \ */
	if (tcon->posix_extensions)
		cifs_sb->mnt_cifs_flags |= CIFS_MOUNT_POSIX_PATHS;

	if (cap_unix(ses))
		reset_cifs_unix_caps(0, tcon, NULL, vol_info);

out:
	kfree(vol_info->username);
	kzfree(vol_info->password);
	kfree(vol_info);

	return tcon;
}