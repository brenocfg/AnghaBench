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
struct TYPE_3__ {int /*<<< orphan*/  so_id; } ;
struct TYPE_4__ {TYPE_1__ si_opaque; } ;
struct nfs4_stid {int /*<<< orphan*/  (* sc_free ) (struct nfs4_stid*) ;TYPE_2__ sc_stateid; int /*<<< orphan*/  sc_count; struct nfs4_client* sc_client; struct nfs4_file* sc_file; } ;
struct nfs4_file {int dummy; } ;
struct nfs4_client {int /*<<< orphan*/  cl_lock; int /*<<< orphan*/  cl_stateids; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_wq ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  might_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_nfs4_file (struct nfs4_file*) ; 
 int /*<<< orphan*/  refcount_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nfs4_stid*) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void
nfs4_put_stid(struct nfs4_stid *s)
{
	struct nfs4_file *fp = s->sc_file;
	struct nfs4_client *clp = s->sc_client;

	might_lock(&clp->cl_lock);

	if (!refcount_dec_and_lock(&s->sc_count, &clp->cl_lock)) {
		wake_up_all(&close_wq);
		return;
	}
	idr_remove(&clp->cl_stateids, s->sc_stateid.si_opaque.so_id);
	spin_unlock(&clp->cl_lock);
	s->sc_free(s);
	if (fp)
		put_nfs4_file(fp);
}