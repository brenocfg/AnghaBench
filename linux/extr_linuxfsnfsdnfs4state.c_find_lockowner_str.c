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
struct xdr_netobj {int dummy; } ;
struct nfs4_lockowner {int dummy; } ;
struct nfs4_client {int /*<<< orphan*/  cl_lock; } ;

/* Variables and functions */
 struct nfs4_lockowner* find_lockowner_str_locked (struct nfs4_client*,struct xdr_netobj*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfs4_lockowner *
find_lockowner_str(struct nfs4_client *clp, struct xdr_netobj *owner)
{
	struct nfs4_lockowner *lo;

	spin_lock(&clp->cl_lock);
	lo = find_lockowner_str_locked(clp, owner);
	spin_unlock(&clp->cl_lock);
	return lo;
}