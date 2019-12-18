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
struct nfsd_file {int /*<<< orphan*/  nf_file; } ;
struct nfs4_stid {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sc_file; } ;
struct nfs4_ol_stateid {TYPE_1__ st_stid; int /*<<< orphan*/  st_stateowner; } ;
struct nfs4_lockowner {int dummy; } ;
typedef  int /*<<< orphan*/  fl_owner_t ;

/* Variables and functions */
 int /*<<< orphan*/  filp_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfsd_file* find_any_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_file (int /*<<< orphan*/ ) ; 
 struct nfs4_lockowner* lockowner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_free_ol_stateid (struct nfs4_stid*) ; 
 int /*<<< orphan*/  nfsd_file_put (struct nfsd_file*) ; 
 struct nfs4_ol_stateid* openlockstateid (struct nfs4_stid*) ; 

__attribute__((used)) static void nfs4_free_lock_stateid(struct nfs4_stid *stid)
{
	struct nfs4_ol_stateid *stp = openlockstateid(stid);
	struct nfs4_lockowner *lo = lockowner(stp->st_stateowner);
	struct nfsd_file *nf;

	nf = find_any_file(stp->st_stid.sc_file);
	if (nf) {
		get_file(nf->nf_file);
		filp_close(nf->nf_file, (fl_owner_t)lo);
		nfsd_file_put(nf);
	}
	nfs4_free_ol_stateid(stid);
}