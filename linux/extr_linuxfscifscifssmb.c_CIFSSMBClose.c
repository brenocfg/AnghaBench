#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  num_closes; } ;
struct TYPE_6__ {TYPE_1__ cifs_stats; } ;
struct cifs_tcon {TYPE_2__ stats; int /*<<< orphan*/  ses; } ;
typedef  scalar_t__ __u16 ;
struct TYPE_7__ {int LastWriteTime; scalar_t__ ByteCount; scalar_t__ FileID; } ;
typedef  TYPE_3__ CLOSE_REQ ;

/* Variables and functions */
 int EAGAIN ; 
 int EINTR ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  SMB_COM_CLOSE ; 
 int SendReceiveNoRsp (unsigned int const,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  cifs_small_buf_release (TYPE_3__*) ; 
 int /*<<< orphan*/  cifs_stats_inc (int /*<<< orphan*/ *) ; 
 int small_smb_init (int /*<<< orphan*/ ,int,struct cifs_tcon*,void**) ; 

int
CIFSSMBClose(const unsigned int xid, struct cifs_tcon *tcon, int smb_file_id)
{
	int rc = 0;
	CLOSE_REQ *pSMB = NULL;
	cifs_dbg(FYI, "In CIFSSMBClose\n");

/* do not retry on dead session on close */
	rc = small_smb_init(SMB_COM_CLOSE, 3, tcon, (void **) &pSMB);
	if (rc == -EAGAIN)
		return 0;
	if (rc)
		return rc;

	pSMB->FileID = (__u16) smb_file_id;
	pSMB->LastWriteTime = 0xFFFFFFFF;
	pSMB->ByteCount = 0;
	rc = SendReceiveNoRsp(xid, tcon->ses, (char *) pSMB, 0);
	cifs_small_buf_release(pSMB);
	cifs_stats_inc(&tcon->stats.cifs_stats.num_closes);
	if (rc) {
		if (rc != -EINTR) {
			/* EINTR is expected when user ctl-c to kill app */
			cifs_dbg(VFS, "Send error in Close = %d\n", rc);
		}
	}

	/* Since session is dead, file will be closed on server already */
	if (rc == -EAGAIN)
		rc = 0;

	return rc;
}