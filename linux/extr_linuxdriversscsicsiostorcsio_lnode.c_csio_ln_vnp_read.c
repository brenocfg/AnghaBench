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
struct csio_lnode {int /*<<< orphan*/  vnp_flowid; int /*<<< orphan*/  fcf_flowid; struct csio_hw* hwp; } ;
struct csio_hw {int /*<<< orphan*/  mb_mempool; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSIO_MB_DEFAULT_TMO ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  csio_err (struct csio_hw*,char*) ; 
 int /*<<< orphan*/  csio_fcoe_vnp_read_init_mb (struct csio_lnode*,struct csio_mb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void (*) (struct csio_hw*,struct csio_mb*)) ; 
 scalar_t__ csio_mb_issue (struct csio_hw*,struct csio_mb*) ; 
 struct csio_mb* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct csio_mb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_err_nomem ; 

__attribute__((used)) static int
csio_ln_vnp_read(struct csio_lnode *ln,
		void (*cbfn) (struct csio_hw *, struct csio_mb *))
{
	struct csio_hw *hw = ln->hwp;
	struct csio_mb  *mbp;

	/* Allocate Mbox request */
	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	if (!mbp) {
		CSIO_INC_STATS(hw, n_err_nomem);
		return -ENOMEM;
	}

	/* Prepare VNP Command */
	csio_fcoe_vnp_read_init_mb(ln, mbp,
				    CSIO_MB_DEFAULT_TMO,
				    ln->fcf_flowid,
				    ln->vnp_flowid,
				    cbfn);

	/* Issue MBOX cmd */
	if (csio_mb_issue(hw, mbp)) {
		csio_err(hw, "Failed to issue mbox FCoE VNP command\n");
		mempool_free(mbp, hw->mb_mempool);
		return -EINVAL;
	}

	return 0;
}