#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct nfs4_file* sc_file; } ;
struct nfs4_ol_stateid {int /*<<< orphan*/  st_perstateowner; int /*<<< orphan*/  st_perfile; TYPE_3__* st_stateowner; TYPE_1__ st_stid; } ;
struct nfs4_file {int /*<<< orphan*/  fi_lock; } ;
struct TYPE_6__ {TYPE_2__* so_client; } ;
struct TYPE_5__ {int /*<<< orphan*/  cl_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool unhash_ol_stateid(struct nfs4_ol_stateid *stp)
{
	struct nfs4_file *fp = stp->st_stid.sc_file;

	lockdep_assert_held(&stp->st_stateowner->so_client->cl_lock);

	if (list_empty(&stp->st_perfile))
		return false;

	spin_lock(&fp->fi_lock);
	list_del_init(&stp->st_perfile);
	spin_unlock(&fp->fi_lock);
	list_del(&stp->st_perstateowner);
	return true;
}