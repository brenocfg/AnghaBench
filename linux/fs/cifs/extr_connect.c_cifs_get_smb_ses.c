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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct smb_vol {int /*<<< orphan*/  local_nls; int /*<<< orphan*/  sign; int /*<<< orphan*/  sectype; int /*<<< orphan*/  linux_uid; int /*<<< orphan*/  cred_uid; scalar_t__ domainauto; scalar_t__ domainname; scalar_t__ password; scalar_t__ username; } ;
struct cifs_ses {int /*<<< orphan*/  smb_ses_list; int /*<<< orphan*/  session_mutex; int /*<<< orphan*/  sign; int /*<<< orphan*/  sectype; int /*<<< orphan*/  linux_uid; int /*<<< orphan*/  cred_uid; scalar_t__ domainAuto; void* domainName; void* password; void* user_name; int /*<<< orphan*/  serverName; struct TCP_Server_Info* server; scalar_t__ need_reconnect; int /*<<< orphan*/  status; } ;
struct TYPE_2__ {scalar_t__ ss_family; } ;
struct TCP_Server_Info {int /*<<< orphan*/  smb_ses_list; TYPE_1__ dstaddr; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int ENOMEM ; 
 struct cifs_ses* ERR_PTR (int) ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 struct cifs_ses* cifs_find_smb_ses (struct TCP_Server_Info*,struct smb_vol*) ; 
 int cifs_negotiate_protocol (unsigned int,struct cifs_ses*) ; 
 int /*<<< orphan*/  cifs_put_smb_ses (struct cifs_ses*) ; 
 int /*<<< orphan*/  cifs_put_tcp_session (struct TCP_Server_Info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_setup_ipc (struct cifs_ses*,struct smb_vol*) ; 
 int cifs_setup_session (unsigned int,struct cifs_ses*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_tcp_ses_lock ; 
 int /*<<< orphan*/  free_xid (unsigned int) ; 
 unsigned int get_xid () ; 
 void* kstrdup (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct cifs_ses* sesInfoAlloc () ; 
 int /*<<< orphan*/  sesInfoFree (struct cifs_ses*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

struct cifs_ses *
cifs_get_smb_ses(struct TCP_Server_Info *server, struct smb_vol *volume_info)
{
	int rc = -ENOMEM;
	unsigned int xid;
	struct cifs_ses *ses;
	struct sockaddr_in *addr = (struct sockaddr_in *)&server->dstaddr;
	struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)&server->dstaddr;

	xid = get_xid();

	ses = cifs_find_smb_ses(server, volume_info);
	if (ses) {
		cifs_dbg(FYI, "Existing smb sess found (status=%d)\n",
			 ses->status);

		mutex_lock(&ses->session_mutex);
		rc = cifs_negotiate_protocol(xid, ses);
		if (rc) {
			mutex_unlock(&ses->session_mutex);
			/* problem -- put our ses reference */
			cifs_put_smb_ses(ses);
			free_xid(xid);
			return ERR_PTR(rc);
		}
		if (ses->need_reconnect) {
			cifs_dbg(FYI, "Session needs reconnect\n");
			rc = cifs_setup_session(xid, ses,
						volume_info->local_nls);
			if (rc) {
				mutex_unlock(&ses->session_mutex);
				/* problem -- put our reference */
				cifs_put_smb_ses(ses);
				free_xid(xid);
				return ERR_PTR(rc);
			}
		}
		mutex_unlock(&ses->session_mutex);

		/* existing SMB ses has a server reference already */
		cifs_put_tcp_session(server, 0);
		free_xid(xid);
		return ses;
	}

	cifs_dbg(FYI, "Existing smb sess not found\n");
	ses = sesInfoAlloc();
	if (ses == NULL)
		goto get_ses_fail;

	/* new SMB session uses our server ref */
	ses->server = server;
	if (server->dstaddr.ss_family == AF_INET6)
		sprintf(ses->serverName, "%pI6", &addr6->sin6_addr);
	else
		sprintf(ses->serverName, "%pI4", &addr->sin_addr);

	if (volume_info->username) {
		ses->user_name = kstrdup(volume_info->username, GFP_KERNEL);
		if (!ses->user_name)
			goto get_ses_fail;
	}

	/* volume_info->password freed at unmount */
	if (volume_info->password) {
		ses->password = kstrdup(volume_info->password, GFP_KERNEL);
		if (!ses->password)
			goto get_ses_fail;
	}
	if (volume_info->domainname) {
		ses->domainName = kstrdup(volume_info->domainname, GFP_KERNEL);
		if (!ses->domainName)
			goto get_ses_fail;
	}
	if (volume_info->domainauto)
		ses->domainAuto = volume_info->domainauto;
	ses->cred_uid = volume_info->cred_uid;
	ses->linux_uid = volume_info->linux_uid;

	ses->sectype = volume_info->sectype;
	ses->sign = volume_info->sign;
	mutex_lock(&ses->session_mutex);
	rc = cifs_negotiate_protocol(xid, ses);
	if (!rc)
		rc = cifs_setup_session(xid, ses, volume_info->local_nls);
	mutex_unlock(&ses->session_mutex);
	if (rc)
		goto get_ses_fail;

	/* success, put it on the list */
	spin_lock(&cifs_tcp_ses_lock);
	list_add(&ses->smb_ses_list, &server->smb_ses_list);
	spin_unlock(&cifs_tcp_ses_lock);

	free_xid(xid);

	cifs_setup_ipc(ses, volume_info);

	return ses;

get_ses_fail:
	sesInfoFree(ses);
	free_xid(xid);
	return ERR_PTR(rc);
}