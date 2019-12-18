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
typedef  int /*<<< orphan*/  u64 ;
struct rb_root {int dummy; } ;
struct TYPE_2__ {scalar_t__ mode; } ;
typedef  int /*<<< orphan*/  GtkTreeStore ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 scalar_t__ CHAIN_FLAT ; 
 scalar_t__ CHAIN_FOLDED ; 
 TYPE_1__ callchain_param ; 
 int /*<<< orphan*/  perf_gtk__add_callchain_flat (struct rb_root*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_gtk__add_callchain_folded (struct rb_root*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_gtk__add_callchain_graph (struct rb_root*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void perf_gtk__add_callchain(struct rb_root *root, GtkTreeStore *store,
				    GtkTreeIter *parent, int col, u64 total)
{
	if (callchain_param.mode == CHAIN_FLAT)
		perf_gtk__add_callchain_flat(root, store, parent, col, total);
	else if (callchain_param.mode == CHAIN_FOLDED)
		perf_gtk__add_callchain_folded(root, store, parent, col, total);
	else
		perf_gtk__add_callchain_graph(root, store, parent, col, total);
}