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
struct nfs_seqid_counter {int /*<<< orphan*/  wait; int /*<<< orphan*/  list; int /*<<< orphan*/  lock; scalar_t__ counter; scalar_t__ flags; int /*<<< orphan*/  create_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  rpc_init_wait_queue (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nfs4_init_seqid_counter(struct nfs_seqid_counter *sc)
{
	sc->create_time = ktime_get();
	sc->flags = 0;
	sc->counter = 0;
	spin_lock_init(&sc->lock);
	INIT_LIST_HEAD(&sc->list);
	rpc_init_wait_queue(&sc->wait, "Seqid_waitqueue");
}