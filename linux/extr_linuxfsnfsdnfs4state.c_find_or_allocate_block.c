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
struct nfsd_net {int dummy; } ;
struct nfsd4_blocked_lock {int /*<<< orphan*/  nbl_cb; int /*<<< orphan*/  nbl_lock; int /*<<< orphan*/  nbl_fh; } ;
struct TYPE_2__ {int /*<<< orphan*/  so_client; } ;
struct nfs4_lockowner {TYPE_1__ lo_owner; } ;
struct knfsd_fh {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NFSPROC4_CLNT_CB_NOTIFY_LOCK ; 
 int /*<<< orphan*/  fh_copy_shallow (int /*<<< orphan*/ *,struct knfsd_fh*) ; 
 struct nfsd4_blocked_lock* find_blocked_lock (struct nfs4_lockowner*,struct knfsd_fh*,struct nfsd_net*) ; 
 struct nfsd4_blocked_lock* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  locks_init_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd4_cb_notify_lock_ops ; 
 int /*<<< orphan*/  nfsd4_init_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nfsd4_blocked_lock *
find_or_allocate_block(struct nfs4_lockowner *lo, struct knfsd_fh *fh,
			struct nfsd_net *nn)
{
	struct nfsd4_blocked_lock *nbl;

	nbl = find_blocked_lock(lo, fh, nn);
	if (!nbl) {
		nbl= kmalloc(sizeof(*nbl), GFP_KERNEL);
		if (nbl) {
			fh_copy_shallow(&nbl->nbl_fh, fh);
			locks_init_lock(&nbl->nbl_lock);
			nfsd4_init_cb(&nbl->nbl_cb, lo->lo_owner.so_client,
					&nfsd4_cb_notify_lock_ops,
					NFSPROC4_CLNT_CB_NOTIFY_LOCK);
		}
	}
	return nbl;
}