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
struct via_display_timing {int hor_total; int hor_addr; int hor_blank_start; int hor_blank_end; int hor_sync_start; int hor_sync_end; int ver_total; int ver_addr; int ver_blank_start; int ver_blank_end; int ver_sync_start; int ver_sync_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIACR ; 
 int /*<<< orphan*/  via_write_reg (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  via_write_reg_mask (int /*<<< orphan*/ ,int,int,int) ; 

void via_set_primary_timing(const struct via_display_timing *timing)
{
	struct via_display_timing raw;

	raw.hor_total = timing->hor_total / 8 - 5;
	raw.hor_addr = timing->hor_addr / 8 - 1;
	raw.hor_blank_start = timing->hor_blank_start / 8 - 1;
	raw.hor_blank_end = timing->hor_blank_end / 8 - 1;
	raw.hor_sync_start = timing->hor_sync_start / 8;
	raw.hor_sync_end = timing->hor_sync_end / 8;
	raw.ver_total = timing->ver_total - 2;
	raw.ver_addr = timing->ver_addr - 1;
	raw.ver_blank_start = timing->ver_blank_start - 1;
	raw.ver_blank_end = timing->ver_blank_end - 1;
	raw.ver_sync_start = timing->ver_sync_start - 1;
	raw.ver_sync_end = timing->ver_sync_end - 1;

	/* unlock timing registers */
	via_write_reg_mask(VIACR, 0x11, 0x00, 0x80);

	via_write_reg(VIACR, 0x00, raw.hor_total & 0xFF);
	via_write_reg(VIACR, 0x01, raw.hor_addr & 0xFF);
	via_write_reg(VIACR, 0x02, raw.hor_blank_start & 0xFF);
	via_write_reg_mask(VIACR, 0x03, raw.hor_blank_end & 0x1F, 0x1F);
	via_write_reg(VIACR, 0x04, raw.hor_sync_start & 0xFF);
	via_write_reg_mask(VIACR, 0x05, (raw.hor_sync_end & 0x1F)
		| (raw.hor_blank_end << (7 - 5) & 0x80), 0x9F);
	via_write_reg(VIACR, 0x06, raw.ver_total & 0xFF);
	via_write_reg_mask(VIACR, 0x07, (raw.ver_total >> 8 & 0x01)
		| (raw.ver_addr >> (8 - 1) & 0x02)
		| (raw.ver_sync_start >> (8 - 2) & 0x04)
		| (raw.ver_blank_start >> (8 - 3) & 0x08)
		| (raw.ver_total >> (9 - 5) & 0x20)
		| (raw.ver_addr >> (9 - 6) & 0x40)
		| (raw.ver_sync_start >> (9 - 7) & 0x80), 0xEF);
	via_write_reg_mask(VIACR, 0x09, raw.ver_blank_start >> (9 - 5) & 0x20,
		0x20);
	via_write_reg(VIACR, 0x10, raw.ver_sync_start & 0xFF);
	via_write_reg_mask(VIACR, 0x11, raw.ver_sync_end & 0x0F, 0x0F);
	via_write_reg(VIACR, 0x12, raw.ver_addr & 0xFF);
	via_write_reg(VIACR, 0x15, raw.ver_blank_start & 0xFF);
	via_write_reg(VIACR, 0x16, raw.ver_blank_end & 0xFF);
	via_write_reg_mask(VIACR, 0x33, (raw.hor_sync_start >> (8 - 4) & 0x10)
		| (raw.hor_blank_end >> (6 - 5) & 0x20), 0x30);
	via_write_reg_mask(VIACR, 0x35, (raw.ver_total >> 10 & 0x01)
		| (raw.ver_sync_start >> (10 - 1) & 0x02)
		| (raw.ver_addr >> (10 - 2) & 0x04)
		| (raw.ver_blank_start >> (10 - 3) & 0x08), 0x0F);
	via_write_reg_mask(VIACR, 0x36, raw.hor_total >> (8 - 3) & 0x08, 0x08);

	/* lock timing registers */
	via_write_reg_mask(VIACR, 0x11, 0x80, 0x80);

	/* reset timing control */
	via_write_reg_mask(VIACR, 0x17, 0x00, 0x80);
	via_write_reg_mask(VIACR, 0x17, 0x80, 0x80);
}