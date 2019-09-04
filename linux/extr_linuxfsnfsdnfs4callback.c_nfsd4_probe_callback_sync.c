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
struct nfs4_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  callback_wq ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd4_probe_callback (struct nfs4_client*) ; 

void nfsd4_probe_callback_sync(struct nfs4_client *clp)
{
	nfsd4_probe_callback(clp);
	flush_workqueue(callback_wq);
}