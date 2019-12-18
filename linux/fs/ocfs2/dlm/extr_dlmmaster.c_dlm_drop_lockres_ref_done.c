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
typedef  int u8 ;
struct TYPE_2__ {char* name; unsigned int len; } ;
struct dlm_lock_resource {TYPE_1__ lockname; } ;
struct dlm_deref_lockres_done {unsigned int namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  node_idx; } ;
struct dlm_ctxt {int /*<<< orphan*/  name; int /*<<< orphan*/  key; int /*<<< orphan*/  node_num; } ;
typedef  int /*<<< orphan*/  deref ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DLM_DEREF_LOCKRES_DONE ; 
 int /*<<< orphan*/  ML_ERROR ; 
 unsigned int O2NM_MAX_NAME_LEN ; 
 int /*<<< orphan*/  dlm_print_one_lock_resource (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,unsigned int) ; 
 int /*<<< orphan*/  memset (struct dlm_deref_lockres_done*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int,char const*,int,int) ; 
 int o2net_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_deref_lockres_done*,int,int,int*) ; 

__attribute__((used)) static void dlm_drop_lockres_ref_done(struct dlm_ctxt *dlm,
		struct dlm_lock_resource *res, u8 node)
{
	struct dlm_deref_lockres_done deref;
	int ret = 0, r;
	const char *lockname;
	unsigned int namelen;

	lockname = res->lockname.name;
	namelen = res->lockname.len;
	BUG_ON(namelen > O2NM_MAX_NAME_LEN);

	memset(&deref, 0, sizeof(deref));
	deref.node_idx = dlm->node_num;
	deref.namelen = namelen;
	memcpy(deref.name, lockname, namelen);

	ret = o2net_send_message(DLM_DEREF_LOCKRES_DONE, dlm->key,
				 &deref, sizeof(deref), node, &r);
	if (ret < 0) {
		mlog(ML_ERROR, "%s: res %.*s, error %d send DEREF DONE "
				" to node %u\n", dlm->name, namelen,
				lockname, ret, node);
	} else if (r < 0) {
		/* ignore the error */
		mlog(ML_ERROR, "%s: res %.*s, DEREF to node %u got %d\n",
		     dlm->name, namelen, lockname, node, r);
		dlm_print_one_lock_resource(res);
	}
}