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
typedef  void* u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct phytbl_info {void* tbl_offset; void* tbl_width; void* tbl_len; int /*<<< orphan*/  const* tbl_ptr; void* tbl_id; } ;
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wlc_lcnphy_write_table (struct brcms_phy*,struct phytbl_info*) ; 

__attribute__((used)) static void
wlc_lcnphy_common_write_table(struct brcms_phy *pi, u32 tbl_id,
			      const u16 *tbl_ptr, u32 tbl_len,
			      u32 tbl_width, u32 tbl_offset)
{

	struct phytbl_info tab;
	tab.tbl_id = tbl_id;
	tab.tbl_ptr = tbl_ptr;
	tab.tbl_len = tbl_len;
	tab.tbl_width = tbl_width;
	tab.tbl_offset = tbl_offset;
	wlc_lcnphy_write_table(pi, &tab);
}