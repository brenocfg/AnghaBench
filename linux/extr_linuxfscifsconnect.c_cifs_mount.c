#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tcon_link {int /*<<< orphan*/  tl_flags; int /*<<< orphan*/  tl_time; struct cifs_tcon* tl_tcon; int /*<<< orphan*/  tl_uid; } ;
struct smb_vol {int max_credits; int persistent; } ;
struct TYPE_8__ {int /*<<< orphan*/  Capability; } ;
struct cifs_tcon {int max_credits; int Flags; int /*<<< orphan*/  linux_uid; TYPE_4__* ops; int /*<<< orphan*/  pipe; scalar_t__ unix_ext; TYPE_3__ fsUnixInfo; TYPE_5__* ses; scalar_t__ posix_extensions; TYPE_1__* server; } ;
struct cifs_ses {int max_credits; int Flags; int /*<<< orphan*/  linux_uid; TYPE_4__* ops; int /*<<< orphan*/  pipe; scalar_t__ unix_ext; TYPE_3__ fsUnixInfo; TYPE_5__* ses; scalar_t__ posix_extensions; TYPE_1__* server; } ;
struct cifs_sb_info {int /*<<< orphan*/  prune_tlinks; int /*<<< orphan*/  tlink_tree_lock; int /*<<< orphan*/  tlink_tree; struct tcon_link* master_tlink; int /*<<< orphan*/  mnt_cifs_flags; int /*<<< orphan*/  rsize; int /*<<< orphan*/  wsize; } ;
struct TCP_Server_Info {int max_credits; int Flags; int /*<<< orphan*/  linux_uid; TYPE_4__* ops; int /*<<< orphan*/  pipe; scalar_t__ unix_ext; TYPE_3__ fsUnixInfo; TYPE_5__* ses; scalar_t__ posix_extensions; TYPE_1__* server; } ;
struct TYPE_10__ {TYPE_2__* server; } ;
struct TYPE_9__ {int (* is_path_accessible ) (unsigned int,struct cifs_tcon*,struct cifs_sb_info*,char*) ;int /*<<< orphan*/  (* negotiate_rsize ) (struct cifs_tcon*,struct smb_vol*) ;int /*<<< orphan*/  (* negotiate_wsize ) (struct cifs_tcon*,struct smb_vol*) ;int /*<<< orphan*/  (* qfs_tcon ) (unsigned int,struct cifs_tcon*) ;} ;
struct TYPE_7__ {scalar_t__ tcpStatus; } ;
struct TYPE_6__ {int capabilities; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_MOUNT_POSIX_PATHS ; 
 int /*<<< orphan*/  CIFS_MOUNT_USE_PREFIX_PATH ; 
 int CIFS_UNIX_TRANSPORT_ENCRYPTION_MANDATORY_CAP ; 
 scalar_t__ CifsNeedReconnect ; 
 int EACCES ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int EOPNOTSUPP ; 
 int EREMOTE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct cifs_tcon*) ; 
 int PTR_ERR (struct cifs_tcon*) ; 
 int SMB2_GLOBAL_CAP_PERSISTENT_HANDLES ; 
 int SMB2_MAX_CREDITS_AVAILABLE ; 
 int SMB_SHARE_IS_IN_DFS ; 
 int /*<<< orphan*/  TCON_LINK_IN_TREE ; 
 int /*<<< orphan*/  TCON_LINK_MASTER ; 
 int /*<<< orphan*/  TLINK_IDLE_EXPIRE ; 
 int /*<<< orphan*/  VFS ; 
 scalar_t__ cap_unix (TYPE_5__*) ; 
 int cifs_are_all_path_components_accessible (struct cifs_tcon*,unsigned int,struct cifs_tcon*,struct cifs_sb_info*,char*) ; 
 char* cifs_build_path_to_root (struct smb_vol*,struct cifs_sb_info*,struct cifs_tcon*,int) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 struct cifs_tcon* cifs_get_smb_ses (struct cifs_tcon*,struct smb_vol*) ; 
 struct cifs_tcon* cifs_get_tcon (struct cifs_tcon*,struct smb_vol*) ; 
 struct cifs_tcon* cifs_get_tcp_session (struct smb_vol*) ; 
 int /*<<< orphan*/  cifs_put_smb_ses (struct cifs_tcon*) ; 
 int /*<<< orphan*/  cifs_put_tcon (struct cifs_tcon*) ; 
 int /*<<< orphan*/  cifs_put_tcp_session (struct cifs_tcon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifsiod_wq ; 
 int /*<<< orphan*/  free_xid (unsigned int) ; 
 unsigned int get_xid () ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (char*) ; 
 struct tcon_link* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_cifs_unix_caps (unsigned int,struct cifs_tcon*,struct cifs_sb_info*,struct smb_vol*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (unsigned int,struct cifs_tcon*) ; 
 int /*<<< orphan*/  stub2 (struct cifs_tcon*,struct smb_vol*) ; 
 int /*<<< orphan*/  stub3 (struct cifs_tcon*,struct smb_vol*) ; 
 int stub4 (unsigned int,struct cifs_tcon*,struct cifs_sb_info*,char*) ; 
 int /*<<< orphan*/  tlink_rb_insert (int /*<<< orphan*/ *,struct tcon_link*) ; 

int
cifs_mount(struct cifs_sb_info *cifs_sb, struct smb_vol *volume_info)
{
	int rc;
	unsigned int xid;
	struct cifs_ses *ses;
	struct cifs_tcon *tcon;
	struct TCP_Server_Info *server;
	char   *full_path;
	struct tcon_link *tlink;
#ifdef CONFIG_CIFS_DFS_UPCALL
	int referral_walks_count = 0;
#endif

#ifdef CONFIG_CIFS_DFS_UPCALL
try_mount_again:
	/* cleanup activities if we're chasing a referral */
	if (referral_walks_count) {
		if (tcon)
			cifs_put_tcon(tcon);
		else if (ses)
			cifs_put_smb_ses(ses);

		cifs_sb->mnt_cifs_flags &= ~CIFS_MOUNT_POSIX_PATHS;

		free_xid(xid);
	}
#endif
	rc = 0;
	tcon = NULL;
	ses = NULL;
	server = NULL;
	full_path = NULL;
	tlink = NULL;

	xid = get_xid();

	/* get a reference to a tcp session */
	server = cifs_get_tcp_session(volume_info);
	if (IS_ERR(server)) {
		rc = PTR_ERR(server);
		goto out;
	}
	if ((volume_info->max_credits < 20) ||
	     (volume_info->max_credits > 60000))
		server->max_credits = SMB2_MAX_CREDITS_AVAILABLE;
	else
		server->max_credits = volume_info->max_credits;
	/* get a reference to a SMB session */
	ses = cifs_get_smb_ses(server, volume_info);
	if (IS_ERR(ses)) {
		rc = PTR_ERR(ses);
		ses = NULL;
		goto mount_fail_check;
	}

	if ((volume_info->persistent == true) && ((ses->server->capabilities &
		SMB2_GLOBAL_CAP_PERSISTENT_HANDLES) == 0)) {
		cifs_dbg(VFS, "persistent handles not supported by server\n");
		rc = -EOPNOTSUPP;
		goto mount_fail_check;
	}

	/* search for existing tcon to this server share */
	tcon = cifs_get_tcon(ses, volume_info);
	if (IS_ERR(tcon)) {
		rc = PTR_ERR(tcon);
		tcon = NULL;
		if (rc == -EACCES)
			goto mount_fail_check;

		goto remote_path_check;
	}

	/* if new SMB3.11 POSIX extensions are supported do not remap / and \ */
	if (tcon->posix_extensions)
		cifs_sb->mnt_cifs_flags |= CIFS_MOUNT_POSIX_PATHS;

	/* tell server which Unix caps we support */
	if (cap_unix(tcon->ses)) {
		/* reset of caps checks mount to see if unix extensions
		   disabled for just this mount */
		reset_cifs_unix_caps(xid, tcon, cifs_sb, volume_info);
		if ((tcon->ses->server->tcpStatus == CifsNeedReconnect) &&
		    (le64_to_cpu(tcon->fsUnixInfo.Capability) &
		     CIFS_UNIX_TRANSPORT_ENCRYPTION_MANDATORY_CAP)) {
			rc = -EACCES;
			goto mount_fail_check;
		}
	} else
		tcon->unix_ext = 0; /* server does not support them */

	/* do not care if a following call succeed - informational */
	if (!tcon->pipe && server->ops->qfs_tcon)
		server->ops->qfs_tcon(xid, tcon);

	cifs_sb->wsize = server->ops->negotiate_wsize(tcon, volume_info);
	cifs_sb->rsize = server->ops->negotiate_rsize(tcon, volume_info);

remote_path_check:
#ifdef CONFIG_CIFS_DFS_UPCALL
	/*
	 * Perform an unconditional check for whether there are DFS
	 * referrals for this path without prefix, to provide support
	 * for DFS referrals from w2k8 servers which don't seem to respond
	 * with PATH_NOT_COVERED to requests that include the prefix.
	 * Chase the referral if found, otherwise continue normally.
	 */
	if (referral_walks_count == 0) {
		int refrc = expand_dfs_referral(xid, ses, volume_info, cifs_sb,
						false);
		if (!refrc) {
			referral_walks_count++;
			goto try_mount_again;
		}
	}
#endif

	/* check if a whole path is not remote */
	if (!rc && tcon) {
		if (!server->ops->is_path_accessible) {
			rc = -ENOSYS;
			goto mount_fail_check;
		}
		/*
		 * cifs_build_path_to_root works only when we have a valid tcon
		 */
		full_path = cifs_build_path_to_root(volume_info, cifs_sb, tcon,
					tcon->Flags & SMB_SHARE_IS_IN_DFS);
		if (full_path == NULL) {
			rc = -ENOMEM;
			goto mount_fail_check;
		}
		rc = server->ops->is_path_accessible(xid, tcon, cifs_sb,
						     full_path);
		if (rc != 0 && rc != -EREMOTE) {
			kfree(full_path);
			goto mount_fail_check;
		}

		if (rc != -EREMOTE) {
			rc = cifs_are_all_path_components_accessible(server,
							     xid, tcon, cifs_sb,
							     full_path);
			if (rc != 0) {
				cifs_dbg(VFS, "cannot query dirs between root and final path, "
					 "enabling CIFS_MOUNT_USE_PREFIX_PATH\n");
				cifs_sb->mnt_cifs_flags |= CIFS_MOUNT_USE_PREFIX_PATH;
				rc = 0;
			}
		}
		kfree(full_path);
	}

	/* get referral if needed */
	if (rc == -EREMOTE) {
#ifdef CONFIG_CIFS_DFS_UPCALL
		if (referral_walks_count > MAX_NESTED_LINKS) {
			/*
			 * BB: when we implement proper loop detection,
			 *     we will remove this check. But now we need it
			 *     to prevent an indefinite loop if 'DFS tree' is
			 *     misconfigured (i.e. has loops).
			 */
			rc = -ELOOP;
			goto mount_fail_check;
		}

		rc = expand_dfs_referral(xid, ses, volume_info, cifs_sb, true);

		if (!rc) {
			referral_walks_count++;
			goto try_mount_again;
		}
		goto mount_fail_check;
#else /* No DFS support, return error on mount */
		rc = -EOPNOTSUPP;
#endif
	}

	if (rc)
		goto mount_fail_check;

	/* now, hang the tcon off of the superblock */
	tlink = kzalloc(sizeof *tlink, GFP_KERNEL);
	if (tlink == NULL) {
		rc = -ENOMEM;
		goto mount_fail_check;
	}

	tlink->tl_uid = ses->linux_uid;
	tlink->tl_tcon = tcon;
	tlink->tl_time = jiffies;
	set_bit(TCON_LINK_MASTER, &tlink->tl_flags);
	set_bit(TCON_LINK_IN_TREE, &tlink->tl_flags);

	cifs_sb->master_tlink = tlink;
	spin_lock(&cifs_sb->tlink_tree_lock);
	tlink_rb_insert(&cifs_sb->tlink_tree, tlink);
	spin_unlock(&cifs_sb->tlink_tree_lock);

	queue_delayed_work(cifsiod_wq, &cifs_sb->prune_tlinks,
				TLINK_IDLE_EXPIRE);

mount_fail_check:
	/* on error free sesinfo and tcon struct if needed */
	if (rc) {
		/* If find_unc succeeded then rc == 0 so we can not end */
		/* up accidentally freeing someone elses tcon struct */
		if (tcon)
			cifs_put_tcon(tcon);
		else if (ses)
			cifs_put_smb_ses(ses);
		else
			cifs_put_tcp_session(server, 0);
	}

out:
	free_xid(xid);
	return rc;
}