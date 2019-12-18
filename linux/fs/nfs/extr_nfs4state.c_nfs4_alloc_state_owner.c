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
struct nfs_server {int /*<<< orphan*/  openowner_id; } ;
struct TYPE_2__ {scalar_t__ owner_id; } ;
struct nfs4_state_owner {int /*<<< orphan*/  so_delegreturn_mutex; int /*<<< orphan*/  so_reclaim_seqcount; int /*<<< orphan*/  so_lru; int /*<<< orphan*/  so_count; TYPE_1__ so_seqid; int /*<<< orphan*/  so_states; int /*<<< orphan*/  so_lock; int /*<<< orphan*/  so_cred; struct nfs_server* so_server; } ;
struct cred {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_cred (struct cred const*) ; 
 scalar_t__ ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfs4_state_owner*) ; 
 struct nfs4_state_owner* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_init_seqid_counter (TYPE_1__*) ; 
 int /*<<< orphan*/  seqcount_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfs4_state_owner *
nfs4_alloc_state_owner(struct nfs_server *server,
		const struct cred *cred,
		gfp_t gfp_flags)
{
	struct nfs4_state_owner *sp;

	sp = kzalloc(sizeof(*sp), gfp_flags);
	if (!sp)
		return NULL;
	sp->so_seqid.owner_id = ida_simple_get(&server->openowner_id, 0, 0,
						gfp_flags);
	if (sp->so_seqid.owner_id < 0) {
		kfree(sp);
		return NULL;
	}
	sp->so_server = server;
	sp->so_cred = get_cred(cred);
	spin_lock_init(&sp->so_lock);
	INIT_LIST_HEAD(&sp->so_states);
	nfs4_init_seqid_counter(&sp->so_seqid);
	atomic_set(&sp->so_count, 1);
	INIT_LIST_HEAD(&sp->so_lru);
	seqcount_init(&sp->so_reclaim_seqcount);
	mutex_init(&sp->so_delegreturn_mutex);
	return sp;
}