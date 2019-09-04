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
struct smb_hdr {int dummy; } ;
struct cifs_tcon {TYPE_1__* ses; scalar_t__ need_reconnect; } ;
struct TYPE_2__ {scalar_t__ need_reconnect; int /*<<< orphan*/ * server; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  SMB_COM_TREE_DISCONNECT ; 
 int SendReceiveNoRsp (unsigned int const,TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  cifs_small_buf_release (struct smb_hdr*) ; 
 int small_smb_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cifs_tcon*,void**) ; 

int
CIFSSMBTDis(const unsigned int xid, struct cifs_tcon *tcon)
{
	struct smb_hdr *smb_buffer;
	int rc = 0;

	cifs_dbg(FYI, "In tree disconnect\n");

	/* BB: do we need to check this? These should never be NULL. */
	if ((tcon->ses == NULL) || (tcon->ses->server == NULL))
		return -EIO;

	/*
	 * No need to return error on this operation if tid invalidated and
	 * closed on server already e.g. due to tcp session crashing. Also,
	 * the tcon is no longer on the list, so no need to take lock before
	 * checking this.
	 */
	if ((tcon->need_reconnect) || (tcon->ses->need_reconnect))
		return 0;

	rc = small_smb_init(SMB_COM_TREE_DISCONNECT, 0, tcon,
			    (void **)&smb_buffer);
	if (rc)
		return rc;

	rc = SendReceiveNoRsp(xid, tcon->ses, (char *)smb_buffer, 0);
	cifs_small_buf_release(smb_buffer);
	if (rc)
		cifs_dbg(FYI, "Tree disconnect failed %d\n", rc);

	/* No need to return error on this operation if tid invalidated and
	   closed on server already e.g. due to tcp session crashing */
	if (rc == -EAGAIN)
		rc = 0;

	return rc;
}