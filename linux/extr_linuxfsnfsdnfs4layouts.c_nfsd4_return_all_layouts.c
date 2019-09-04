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
struct nfs4_layout_stateid {int /*<<< orphan*/  ls_lock; int /*<<< orphan*/  ls_layouts; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nfsd4_return_all_layouts(struct nfs4_layout_stateid *ls,
		struct list_head *reaplist)
{
	spin_lock(&ls->ls_lock);
	list_splice_init(&ls->ls_layouts, reaplist);
	spin_unlock(&ls->ls_lock);
}