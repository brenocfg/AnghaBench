#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  scalar_t__ u16 ;
struct fcoe_bd_ctx {int buf_addr_lo; int buf_addr_hi; scalar_t__ flags; scalar_t__ buf_len; } ;
struct bnx2fc_cmd {TYPE_1__* bd_tbl; } ;
struct TYPE_2__ {struct fcoe_bd_ctx* bd_tbl; } ;

/* Variables and functions */
 int BNX2FC_BD_SPLIT_SZ ; 

__attribute__((used)) static int bnx2fc_split_bd(struct bnx2fc_cmd *io_req, u64 addr, int sg_len,
			   int bd_index)
{
	struct fcoe_bd_ctx *bd = io_req->bd_tbl->bd_tbl;
	int frag_size, sg_frags;

	sg_frags = 0;
	while (sg_len) {
		if (sg_len >= BNX2FC_BD_SPLIT_SZ)
			frag_size = BNX2FC_BD_SPLIT_SZ;
		else
			frag_size = sg_len;
		bd[bd_index + sg_frags].buf_addr_lo = addr & 0xffffffff;
		bd[bd_index + sg_frags].buf_addr_hi  = addr >> 32;
		bd[bd_index + sg_frags].buf_len = (u16)frag_size;
		bd[bd_index + sg_frags].flags = 0;

		addr += (u64) frag_size;
		sg_frags++;
		sg_len -= frag_size;
	}
	return sg_frags;

}