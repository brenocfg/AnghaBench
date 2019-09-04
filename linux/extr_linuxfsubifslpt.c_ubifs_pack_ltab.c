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
typedef  int /*<<< orphan*/  uint16_t ;
struct ubifs_lpt_lprops {int /*<<< orphan*/  dirty; int /*<<< orphan*/  free; } ;
struct ubifs_info {int lpt_lebs; int ltab_sz; int /*<<< orphan*/  lpt_spc_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  UBIFS_LPT_CRC_BITS ; 
 int UBIFS_LPT_CRC_BYTES ; 
 int /*<<< orphan*/  UBIFS_LPT_LTAB ; 
 int /*<<< orphan*/  UBIFS_LPT_TYPE_BITS ; 
 int /*<<< orphan*/  crc16 (int,void*,int) ; 
 int /*<<< orphan*/  pack_bits (struct ubifs_info*,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ubifs_pack_ltab(struct ubifs_info *c, void *buf,
		     struct ubifs_lpt_lprops *ltab)
{
	uint8_t *addr = buf + UBIFS_LPT_CRC_BYTES;
	int i, pos = 0;
	uint16_t crc;

	pack_bits(c, &addr, &pos, UBIFS_LPT_LTAB, UBIFS_LPT_TYPE_BITS);
	for (i = 0; i < c->lpt_lebs; i++) {
		pack_bits(c, &addr, &pos, ltab[i].free, c->lpt_spc_bits);
		pack_bits(c, &addr, &pos, ltab[i].dirty, c->lpt_spc_bits);
	}
	crc = crc16(-1, buf + UBIFS_LPT_CRC_BYTES,
		    c->ltab_sz - UBIFS_LPT_CRC_BYTES);
	addr = buf;
	pos = 0;
	pack_bits(c, &addr, &pos, crc, UBIFS_LPT_CRC_BITS);
}