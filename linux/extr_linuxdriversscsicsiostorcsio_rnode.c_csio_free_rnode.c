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
struct csio_rnode {int /*<<< orphan*/  lnp; } ;
struct csio_hw {int /*<<< orphan*/  rnode_mempool; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct csio_hw* csio_lnode_to_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_rnode_exit (struct csio_rnode*) ; 
 int /*<<< orphan*/  csio_rnode_to_lnode (struct csio_rnode*) ; 
 int /*<<< orphan*/  mempool_free (struct csio_rnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_rnode_free ; 

__attribute__((used)) static void
csio_free_rnode(struct csio_rnode *rn)
{
	struct csio_hw *hw = csio_lnode_to_hw(csio_rnode_to_lnode(rn));

	csio_rnode_exit(rn);
	CSIO_INC_STATS(rn->lnp, n_rnode_free);
	mempool_free(rn, hw->rnode_mempool);
}