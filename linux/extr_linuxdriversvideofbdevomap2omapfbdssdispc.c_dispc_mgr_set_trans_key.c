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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum omap_dss_trans_key_type { ____Placeholder_omap_dss_trans_key_type } omap_dss_trans_key_type ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_MGR_FLD_TCKSELECTION ; 
 int /*<<< orphan*/  DISPC_TRANS_COLOR (int) ; 
 int /*<<< orphan*/  dispc_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgr_fld_write (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dispc_mgr_set_trans_key(enum omap_channel ch,
		enum omap_dss_trans_key_type type,
		u32 trans_key)
{
	mgr_fld_write(ch, DISPC_MGR_FLD_TCKSELECTION, type);

	dispc_write_reg(DISPC_TRANS_COLOR(ch), trans_key);
}