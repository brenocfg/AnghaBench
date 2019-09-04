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
struct nfs4_state {int dummy; } ;
struct nfs4_lock_state {int dummy; } ;
struct TYPE_3__ {struct nfs4_lock_state* owner; } ;
struct TYPE_4__ {TYPE_1__ nfs4_fl; } ;
struct file_lock {int /*<<< orphan*/ * fl_ops; TYPE_2__ fl_u; int /*<<< orphan*/  fl_owner; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  nfs4_fl_lock_ops ; 
 struct nfs4_lock_state* nfs4_get_lock_state (struct nfs4_state*,int /*<<< orphan*/ ) ; 

int nfs4_set_lock_state(struct nfs4_state *state, struct file_lock *fl)
{
	struct nfs4_lock_state *lsp;

	if (fl->fl_ops != NULL)
		return 0;
	lsp = nfs4_get_lock_state(state, fl->fl_owner);
	if (lsp == NULL)
		return -ENOMEM;
	fl->fl_u.nfs4_fl.owner = lsp;
	fl->fl_ops = &nfs4_fl_lock_ops;
	return 0;
}