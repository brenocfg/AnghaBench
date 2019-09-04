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
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dlm_lock_resource {int /*<<< orphan*/  hash_node; TYPE_1__ lockname; } ;
struct dlm_ctxt {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dlm_lockres_put (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ hlist_unhashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void __dlm_unhash_lockres(struct dlm_ctxt *dlm, struct dlm_lock_resource *res)
{
	if (hlist_unhashed(&res->hash_node))
		return;

	mlog(0, "%s: Unhash res %.*s\n", dlm->name, res->lockname.len,
	     res->lockname.name);
	hlist_del_init(&res->hash_node);
	dlm_lockres_put(res);
}