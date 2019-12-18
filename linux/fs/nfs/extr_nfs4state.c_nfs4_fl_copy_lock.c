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
struct nfs4_lock_state {int /*<<< orphan*/  ls_count; } ;
struct TYPE_3__ {struct nfs4_lock_state* owner; } ;
struct TYPE_4__ {TYPE_1__ nfs4_fl; } ;
struct file_lock {TYPE_2__ fl_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs4_fl_copy_lock(struct file_lock *dst, struct file_lock *src)
{
	struct nfs4_lock_state *lsp = src->fl_u.nfs4_fl.owner;

	dst->fl_u.nfs4_fl.owner = lsp;
	refcount_inc(&lsp->ls_count);
}