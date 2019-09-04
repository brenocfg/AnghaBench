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
struct csio_mb {int dummy; } ;
struct csio_hw {int /*<<< orphan*/  mb_mempool; int /*<<< orphan*/  pfn; } ;
struct csio_eq_params {int /*<<< orphan*/  eqid; scalar_t__ vfn; int /*<<< orphan*/  pfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_MB_DEFAULT_TMO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  csio_mb_eq_ofld_free (struct csio_hw*,struct csio_mb*,void*,int /*<<< orphan*/ ,struct csio_eq_params*,void (*) (struct csio_hw*,struct csio_mb*)) ; 
 int csio_mb_issue (struct csio_hw*,struct csio_mb*) ; 
 int /*<<< orphan*/  csio_q_eqid (struct csio_hw*,int) ; 
 int csio_wr_eq_destroy_rsp (struct csio_hw*,struct csio_mb*,int) ; 
 struct csio_mb* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct csio_mb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct csio_eq_params*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
csio_wr_eq_destroy(struct csio_hw *hw, void *priv, int eq_idx,
		   void (*cbfn) (struct csio_hw *, struct csio_mb *))
{
	int rv = 0;
	struct csio_mb  *mbp;
	struct csio_eq_params eqp;

	memset(&eqp, 0, sizeof(struct csio_eq_params));

	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	if (!mbp)
		return -ENOMEM;

	eqp.pfn		= hw->pfn;
	eqp.vfn		= 0;
	eqp.eqid	= csio_q_eqid(hw, eq_idx);

	csio_mb_eq_ofld_free(hw, mbp, priv, CSIO_MB_DEFAULT_TMO, &eqp, cbfn);

	rv = csio_mb_issue(hw, mbp);
	if (rv != 0) {
		mempool_free(mbp, hw->mb_mempool);
		return rv;
	}

	if (cbfn != NULL)
		return 0;

	return csio_wr_eq_destroy_rsp(hw, mbp, eq_idx);
}