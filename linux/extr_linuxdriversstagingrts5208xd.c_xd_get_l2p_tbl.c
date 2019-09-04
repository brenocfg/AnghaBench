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
typedef  int u32 ;
typedef  size_t u16 ;
struct zone_entry {int* l2p_table; int unused_blk_cnt; } ;
struct xd_info {scalar_t__ page_off; struct zone_entry* zone; } ;
struct rtsx_chip {struct xd_info xd_card; } ;

/* Variables and functions */
 int BLK_NOT_FOUND ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int xd_get_unused_block (struct rtsx_chip*,int) ; 
 int xd_init_page (struct rtsx_chip*,int,size_t,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xd_set_l2p_tbl (struct rtsx_chip*,int,size_t,size_t) ; 

__attribute__((used)) static u32 xd_get_l2p_tbl(struct rtsx_chip *chip, int zone_no, u16 log_off)
{
	struct xd_info *xd_card = &chip->xd_card;
	struct zone_entry *zone;
	int retval;

	zone = &xd_card->zone[zone_no];
	if (zone->l2p_table[log_off] == 0xFFFF) {
		u32 phy_blk = 0;
		int i;

#ifdef XD_DELAY_WRITE
		retval = xd_delay_write(chip);
		if (retval != STATUS_SUCCESS) {
			dev_dbg(rtsx_dev(chip), "In %s, delay write fail!\n",
				__func__);
			return BLK_NOT_FOUND;
		}
#endif

		if (zone->unused_blk_cnt <= 0) {
			dev_dbg(rtsx_dev(chip), "No unused block!\n");
			return BLK_NOT_FOUND;
		}

		for (i = 0; i < zone->unused_blk_cnt; i++) {
			phy_blk = xd_get_unused_block(chip, zone_no);
			if (phy_blk == BLK_NOT_FOUND) {
				dev_dbg(rtsx_dev(chip), "No unused block available!\n");
				return BLK_NOT_FOUND;
			}

			retval = xd_init_page(chip, phy_blk, log_off,
					      0, xd_card->page_off + 1);
			if (retval == STATUS_SUCCESS)
				break;
		}
		if (i >= zone->unused_blk_cnt) {
			dev_dbg(rtsx_dev(chip), "No good unused block available!\n");
			return BLK_NOT_FOUND;
		}

		xd_set_l2p_tbl(chip, zone_no, log_off, (u16)(phy_blk & 0x3FF));
		return phy_blk;
	}

	return (u32)zone->l2p_table[log_off] + ((u32)(zone_no) << 10);
}