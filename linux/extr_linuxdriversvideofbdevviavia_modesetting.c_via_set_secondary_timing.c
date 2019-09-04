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

void via_set_secondary_timing(const struct via_display_timing *timing)
{
	struct via_display_timing raw;

	raw.hor_total = timing->hor_total - 1;
	raw.hor_addr = timing->hor_addr - 1;
	raw.hor_blank_start = timing->hor_blank_start - 1;
	raw.hor_blank_end = timing->hor_blank_end - 1;
	raw.hor_sync_start = timing->hor_sync_start - 1;
	raw.hor_sync_end = timing->hor_sync_end - 1;
	raw.ver_total = timing->ver_total - 1;
	raw.ver_addr = timing->ver_addr - 1;
	raw.ver_blank_start = timing->ver_blank_start - 1;
	raw.ver_blank_end = timing->ver_blank_end - 1;
	raw.ver_sync_start = timing->ver_sync_start - 1;
	raw.ver_sync_end = timing->ver_sync_end - 1;

	via_write_reg(VIACR, 0x50, raw.hor_total & 0xFF);
	via_write_reg(VIACR, 0x51, raw.hor_addr & 0xFF);
	via_write_reg(VIACR, 0x52, raw.hor_blank_start & 0xFF);
	via_write_reg(VIACR, 0x53, raw.hor_blank_end & 0xFF);
	via_write_reg(VIACR, 0x54, (raw.hor_blank_start >> 8 & 0x07)
		| (raw.hor_blank_end >> (8 - 3) & 0x38)
		| (raw.hor_sync_start >> (8 - 6) & 0xC0));
	via_write_reg_mask(VIACR, 0x55, (raw.hor_total >> 8 & 0x0F)
		| (raw.hor_addr >> (8 - 4) & 0x70), 0x7F);
	via_write_reg(VIACR, 0x56, raw.hor_sync_start & 0xFF);
	via_write_reg(VIACR, 0x57, raw.hor_sync_end & 0xFF);
	via_write_reg(VIACR, 0x58, raw.ver_total & 0xFF);
	via_write_reg(VIACR, 0x59, raw.ver_addr & 0xFF);
	via_write_reg(VIACR, 0x5A, raw.ver_blank_start & 0xFF);
	via_write_reg(VIACR, 0x5B, raw.ver_blank_end & 0xFF);
	via_write_reg(VIACR, 0x5C, (raw.ver_blank_start >> 8 & 0x07)
		| (raw.ver_blank_end >> (8 - 3) & 0x38)
		| (raw.hor_sync_end >> (8 - 6) & 0x40)
		| (raw.hor_sync_start >> (10 - 7) & 0x80));
	via_write_reg(VIACR, 0x5D, (raw.ver_total >> 8 & 0x07)
		| (raw.ver_addr >> (8 - 3) & 0x38)
		| (raw.hor_blank_end >> (11 - 6) & 0x40)
		| (raw.hor_sync_start >> (11 - 7) & 0x80));
	via_write_reg(VIACR, 0x5E, raw.ver_sync_start & 0xFF);
	via_write_reg(VIACR, 0x5F, (raw.ver_sync_end & 0x1F)
		| (raw.ver_sync_start >> (8 - 5) & 0xE0));
}