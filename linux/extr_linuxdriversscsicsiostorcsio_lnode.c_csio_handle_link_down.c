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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct csio_lnode {int /*<<< orphan*/  fcf_flowid; struct csio_fcf_info* fcfinfo; } ;
struct csio_hw {int /*<<< orphan*/  fcf_flowid; struct csio_fcf_info* fcfinfo; } ;
struct csio_fcf_info {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_lnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_info (struct csio_lnode*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_is_lnode_ready (struct csio_lnode*) ; 
 int /*<<< orphan*/  csio_ln_down (struct csio_lnode*) ; 
 struct csio_lnode* csio_ln_lookup_by_vnpi (struct csio_lnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_ln_warn (struct csio_lnode*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_warn (struct csio_lnode*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_evt_drop ; 
 int /*<<< orphan*/  n_link_down ; 

__attribute__((used)) static void
csio_handle_link_down(struct csio_hw *hw, uint8_t portid, uint32_t fcfi,
		      uint32_t vnpi)
{
	struct csio_fcf_info *fp;
	struct csio_lnode *ln;

	/* Lookup lnode based on vnpi */
	ln = csio_ln_lookup_by_vnpi(hw, vnpi);
	if (ln) {
		fp = ln->fcfinfo;
		CSIO_INC_STATS(ln, n_link_down);

		/*Warn if linkdown received if lnode is not in ready state */
		if (!csio_is_lnode_ready(ln)) {
			csio_ln_warn(ln,
				"warn: FCOE link is already in offline "
				"Ignoring Fcoe linkdown event on portid %d\n",
				 portid);
			CSIO_INC_STATS(ln, n_evt_drop);
			return;
		}

		/* Verify portid */
		if (fp->portid != portid) {
			csio_ln_warn(ln,
				"warn: FCOE linkdown recv with "
				"invalid port %d\n", portid);
			CSIO_INC_STATS(ln, n_evt_drop);
			return;
		}

		/* verify fcfi */
		if (ln->fcf_flowid != fcfi) {
			csio_ln_warn(ln,
				"warn: FCOE linkdown recv with "
				"invalid fcfi x%x\n", fcfi);
			CSIO_INC_STATS(ln, n_evt_drop);
			return;
		}

		csio_info(hw, "Port:%d - FCOE LINK DOWN\n", portid);

		/* Send LINK_DOWN event to lnode s/m */
		csio_ln_down(ln);

		return;
	} else {
		csio_warn(hw,
			  "warn: FCOE linkdown recv with invalid vnpi x%x\n",
			  vnpi);
		CSIO_INC_STATS(hw, n_evt_drop);
	}
}