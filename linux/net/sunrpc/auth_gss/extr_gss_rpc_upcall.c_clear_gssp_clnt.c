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
struct sunrpc_net {int /*<<< orphan*/  gssp_lock; int /*<<< orphan*/ * gssp_clnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_shutdown_client (int /*<<< orphan*/ *) ; 

void clear_gssp_clnt(struct sunrpc_net *sn)
{
	mutex_lock(&sn->gssp_lock);
	if (sn->gssp_clnt) {
		rpc_shutdown_client(sn->gssp_clnt);
		sn->gssp_clnt = NULL;
	}
	mutex_unlock(&sn->gssp_lock);
}