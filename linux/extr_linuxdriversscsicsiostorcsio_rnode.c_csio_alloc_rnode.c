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
struct csio_rnode {int dummy; } ;
struct csio_lnode {int dummy; } ;
struct csio_hw {int /*<<< orphan*/  rnode_mempool; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_lnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct csio_hw* csio_lnode_to_hw (struct csio_lnode*) ; 
 scalar_t__ csio_rnode_init (struct csio_rnode*,struct csio_lnode*) ; 
 struct csio_rnode* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct csio_rnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct csio_rnode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  n_rnode_alloc ; 
 int /*<<< orphan*/  n_rnode_nomem ; 

__attribute__((used)) static struct csio_rnode *
csio_alloc_rnode(struct csio_lnode *ln)
{
	struct csio_hw *hw = csio_lnode_to_hw(ln);

	struct csio_rnode *rn = mempool_alloc(hw->rnode_mempool, GFP_ATOMIC);
	if (!rn)
		goto err;

	memset(rn, 0, sizeof(struct csio_rnode));
	if (csio_rnode_init(rn, ln))
		goto err_free;

	CSIO_INC_STATS(ln, n_rnode_alloc);

	return rn;

err_free:
	mempool_free(rn, hw->rnode_mempool);
err:
	CSIO_INC_STATS(ln, n_rnode_nomem);
	return NULL;
}