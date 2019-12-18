#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cifs_tcon {int dummy; } ;
struct cifs_ses {struct cifs_tcon* tcon_ipc; TYPE_1__* server; } ;
struct TYPE_4__ {int (* tree_disconnect ) (int,struct cifs_tcon*) ;} ;
struct TYPE_3__ {TYPE_2__* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free_xid (int) ; 
 int get_xid () ; 
 int stub1 (int,struct cifs_tcon*) ; 
 int /*<<< orphan*/  tconInfoFree (struct cifs_tcon*) ; 

__attribute__((used)) static int
cifs_free_ipc(struct cifs_ses *ses)
{
	int rc = 0, xid;
	struct cifs_tcon *tcon = ses->tcon_ipc;

	if (tcon == NULL)
		return 0;

	if (ses->server->ops->tree_disconnect) {
		xid = get_xid();
		rc = ses->server->ops->tree_disconnect(xid, tcon);
		free_xid(xid);
	}

	if (rc)
		cifs_dbg(FYI, "failed to disconnect IPC tcon (rc=%d)\n", rc);

	tconInfoFree(tcon);
	ses->tcon_ipc = NULL;
	return rc;
}