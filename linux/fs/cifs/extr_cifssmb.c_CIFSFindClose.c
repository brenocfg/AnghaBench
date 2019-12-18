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
struct TYPE_5__ {int /*<<< orphan*/  num_fclose; } ;
struct TYPE_6__ {TYPE_1__ cifs_stats; } ;
struct cifs_tcon {TYPE_2__ stats; int /*<<< orphan*/  ses; } ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_7__ {scalar_t__ ByteCount; int /*<<< orphan*/  FileID; } ;
typedef  TYPE_3__ FINDCLOSE_REQ ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  SMB_COM_FIND_CLOSE2 ; 
 int SendReceiveNoRsp (unsigned int const,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  cifs_small_buf_release (TYPE_3__*) ; 
 int /*<<< orphan*/  cifs_stats_inc (int /*<<< orphan*/ *) ; 
 int small_smb_init (int /*<<< orphan*/ ,int,struct cifs_tcon*,void**) ; 

int
CIFSFindClose(const unsigned int xid, struct cifs_tcon *tcon,
	      const __u16 searchHandle)
{
	int rc = 0;
	FINDCLOSE_REQ *pSMB = NULL;

	cifs_dbg(FYI, "In CIFSSMBFindClose\n");
	rc = small_smb_init(SMB_COM_FIND_CLOSE2, 1, tcon, (void **)&pSMB);

	/* no sense returning error if session restarted
		as file handle has been closed */
	if (rc == -EAGAIN)
		return 0;
	if (rc)
		return rc;

	pSMB->FileID = searchHandle;
	pSMB->ByteCount = 0;
	rc = SendReceiveNoRsp(xid, tcon->ses, (char *) pSMB, 0);
	cifs_small_buf_release(pSMB);
	if (rc)
		cifs_dbg(VFS, "Send error in FindClose = %d\n", rc);

	cifs_stats_inc(&tcon->stats.cifs_stats.num_fclose);

	/* Since session is dead, search handle closed on server already */
	if (rc == -EAGAIN)
		rc = 0;

	return rc;
}