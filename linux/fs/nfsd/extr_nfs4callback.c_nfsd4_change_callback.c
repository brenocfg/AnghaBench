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
struct nfs4_client {int /*<<< orphan*/  cl_lock; int /*<<< orphan*/  cl_cb_conn; int /*<<< orphan*/  cl_cb_state; } ;
struct nfs4_cb_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSD4_CB_UNKNOWN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct nfs4_cb_conn*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void nfsd4_change_callback(struct nfs4_client *clp, struct nfs4_cb_conn *conn)
{
	clp->cl_cb_state = NFSD4_CB_UNKNOWN;
	spin_lock(&clp->cl_lock);
	memcpy(&clp->cl_cb_conn, conn, sizeof(struct nfs4_cb_conn));
	spin_unlock(&clp->cl_lock);
}