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
struct ar934x_nfc {int addr_count0; scalar_t__ small_page; } ;

/* Variables and functions */

__attribute__((used)) static void ar934x_nfc_get_addr(struct ar934x_nfc *nfc, int column,
				int page_addr, u32 *addr0, u32 *addr1)
{
	u32 a0, a1;

	a0 = 0;
	a1 = 0;

	if (column == -1) {
		/* ERASE1 */
		a0 = (page_addr & 0xffff) << 16;
		a1 = (page_addr >> 16) & 0xf;
	} else if (page_addr != -1) {
		/* SEQIN, READ0, etc.. */

		/* TODO: handle 16bit bus width */
		if (nfc->small_page) {
			a0 = column & 0xff;
			a0 |= (page_addr & 0xff) << 8;
			a0 |= ((page_addr >> 8) & 0xff) << 16;
			a0 |= ((page_addr >> 16) & 0xff) << 24;
		} else {
			a0 = column & 0x0FFF;
			a0 |= (page_addr & 0xffff) << 16;

			if (nfc->addr_count0 > 4)
				a1 = (page_addr >> 16) & 0xf;
		}
	}

	*addr0 = a0;
	*addr1 = a1;
}