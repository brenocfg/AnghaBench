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
struct TYPE_4__ {TYPE_1__* fm_mr; } ;
struct rpcrdma_mr {TYPE_2__ fmr; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int ib_unmap_fmr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
__fmr_unmap(struct rpcrdma_mr *mr)
{
	LIST_HEAD(l);
	int rc;

	list_add(&mr->fmr.fm_mr->list, &l);
	rc = ib_unmap_fmr(&l);
	list_del(&mr->fmr.fm_mr->list);
	return rc;
}