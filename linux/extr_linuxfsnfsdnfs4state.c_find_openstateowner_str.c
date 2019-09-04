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
struct nfsd4_open {int dummy; } ;
struct nfs4_openowner {int dummy; } ;
struct nfs4_client {int /*<<< orphan*/  cl_lock; } ;

/* Variables and functions */
 struct nfs4_openowner* find_openstateowner_str_locked (unsigned int,struct nfsd4_open*,struct nfs4_client*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfs4_openowner *
find_openstateowner_str(unsigned int hashval, struct nfsd4_open *open,
			struct nfs4_client *clp)
{
	struct nfs4_openowner *oo;

	spin_lock(&clp->cl_lock);
	oo = find_openstateowner_str_locked(hashval, open, clp);
	spin_unlock(&clp->cl_lock);
	return oo;
}