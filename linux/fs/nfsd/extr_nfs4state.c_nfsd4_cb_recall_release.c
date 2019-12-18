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
struct nfsd4_callback {int dummy; } ;
struct nfs4_delegation {int /*<<< orphan*/  dl_stid; } ;

/* Variables and functions */
 struct nfs4_delegation* cb_to_delegation (struct nfsd4_callback*) ; 
 int /*<<< orphan*/  nfs4_put_stid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfsd4_cb_recall_release(struct nfsd4_callback *cb)
{
	struct nfs4_delegation *dp = cb_to_delegation(cb);

	nfs4_put_stid(&dp->dl_stid);
}