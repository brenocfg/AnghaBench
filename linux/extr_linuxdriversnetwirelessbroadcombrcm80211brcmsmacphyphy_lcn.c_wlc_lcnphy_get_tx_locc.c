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
typedef  int /*<<< orphan*/  u16 ;
struct phytbl_info {int tbl_width; int tbl_len; int tbl_offset; int /*<<< orphan*/ * tbl_ptr; scalar_t__ tbl_id; } ;
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wlc_lcnphy_read_table (struct brcms_phy*,struct phytbl_info*) ; 

u16 wlc_lcnphy_get_tx_locc(struct brcms_phy *pi)
{
	struct phytbl_info tab;
	u16 didq;

	tab.tbl_id = 0;
	tab.tbl_width = 16;
	tab.tbl_ptr = &didq;
	tab.tbl_len = 1;
	tab.tbl_offset = 85;
	wlc_lcnphy_read_table(pi, &tab);

	return didq;
}