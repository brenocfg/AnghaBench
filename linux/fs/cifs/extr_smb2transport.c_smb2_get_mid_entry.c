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
struct smb2_sync_hdr {scalar_t__ Command; } ;
struct mid_q_entry {int /*<<< orphan*/  qhead; } ;
struct cifs_ses {scalar_t__ status; TYPE_1__* server; } ;
struct TYPE_2__ {scalar_t__ tcpStatus; int /*<<< orphan*/  pending_mid_q; } ;

/* Variables and functions */
 scalar_t__ CifsExiting ; 
 scalar_t__ CifsNeedNegotiate ; 
 scalar_t__ CifsNeedReconnect ; 
 scalar_t__ CifsNew ; 
 int EAGAIN ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  GlobalMid_Lock ; 
 scalar_t__ SMB2_LOGOFF ; 
 scalar_t__ SMB2_NEGOTIATE ; 
 scalar_t__ SMB2_SESSION_SETUP ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mid_q_entry* smb2_mid_entry_alloc (struct smb2_sync_hdr*,TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
smb2_get_mid_entry(struct cifs_ses *ses, struct smb2_sync_hdr *shdr,
		   struct mid_q_entry **mid)
{
	if (ses->server->tcpStatus == CifsExiting)
		return -ENOENT;

	if (ses->server->tcpStatus == CifsNeedReconnect) {
		cifs_dbg(FYI, "tcp session dead - return to caller to retry\n");
		return -EAGAIN;
	}

	if (ses->server->tcpStatus == CifsNeedNegotiate &&
	   shdr->Command != SMB2_NEGOTIATE)
		return -EAGAIN;

	if (ses->status == CifsNew) {
		if ((shdr->Command != SMB2_SESSION_SETUP) &&
		    (shdr->Command != SMB2_NEGOTIATE))
			return -EAGAIN;
		/* else ok - we are setting up session */
	}

	if (ses->status == CifsExiting) {
		if (shdr->Command != SMB2_LOGOFF)
			return -EAGAIN;
		/* else ok - we are shutting down the session */
	}

	*mid = smb2_mid_entry_alloc(shdr, ses->server);
	if (*mid == NULL)
		return -ENOMEM;
	spin_lock(&GlobalMid_Lock);
	list_add_tail(&(*mid)->qhead, &ses->server->pending_mid_q);
	spin_unlock(&GlobalMid_Lock);

	return 0;
}