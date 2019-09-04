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
struct b577xx_doorbell_set_prod {int prod; } ;
struct bnx2fc_rport {int sq_prod_idx; int sq_curr_toggle_bit; int /*<<< orphan*/  ctx_base; struct b577xx_doorbell_set_prod sq_db; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bnx2fc_ring_doorbell(struct bnx2fc_rport *tgt)
{
	struct b577xx_doorbell_set_prod *sq_db = &tgt->sq_db;
	u32 msg;

	wmb();
	sq_db->prod = tgt->sq_prod_idx |
				(tgt->sq_curr_toggle_bit << 15);
	msg = *((u32 *)sq_db);
	writel(cpu_to_le32(msg), tgt->ctx_base);
	mmiowb();

}