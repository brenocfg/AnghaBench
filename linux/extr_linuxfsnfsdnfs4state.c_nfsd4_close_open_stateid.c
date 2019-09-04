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
struct TYPE_2__ {struct nfs4_client* sc_client; } ;
struct nfs4_ol_stateid {TYPE_1__ st_stid; } ;
struct nfs4_client {int /*<<< orphan*/  net; int /*<<< orphan*/  cl_lock; scalar_t__ cl_minorversion; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_ol_stateid_reaplist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  move_to_close_lru (struct nfs4_ol_stateid*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_ol_stateid_locked (struct nfs4_ol_stateid*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reaplist ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int unhash_open_stateid (struct nfs4_ol_stateid*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfsd4_close_open_stateid(struct nfs4_ol_stateid *s)
{
	struct nfs4_client *clp = s->st_stid.sc_client;
	bool unhashed;
	LIST_HEAD(reaplist);

	spin_lock(&clp->cl_lock);
	unhashed = unhash_open_stateid(s, &reaplist);

	if (clp->cl_minorversion) {
		if (unhashed)
			put_ol_stateid_locked(s, &reaplist);
		spin_unlock(&clp->cl_lock);
		free_ol_stateid_reaplist(&reaplist);
	} else {
		spin_unlock(&clp->cl_lock);
		free_ol_stateid_reaplist(&reaplist);
		if (unhashed)
			move_to_close_lru(s, clp->net);
	}
}