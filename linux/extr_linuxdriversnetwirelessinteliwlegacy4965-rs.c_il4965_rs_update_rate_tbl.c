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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct il_scale_tbl_info {int dummy; } ;
struct il_priv {int dummy; } ;
struct il_lq_sta {int /*<<< orphan*/  lq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ASYNC ; 
 int /*<<< orphan*/  il4965_rate_n_flags_from_tbl (struct il_priv*,struct il_scale_tbl_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il4965_rs_fill_link_cmd (struct il_priv*,struct il_lq_sta*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il_send_lq_cmd (struct il_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
il4965_rs_update_rate_tbl(struct il_priv *il, struct il_lq_sta *lq_sta,
			  struct il_scale_tbl_info *tbl, int idx, u8 is_green)
{
	u32 rate;

	/* Update uCode's rate table. */
	rate = il4965_rate_n_flags_from_tbl(il, tbl, idx, is_green);
	il4965_rs_fill_link_cmd(il, lq_sta, rate);
	il_send_lq_cmd(il, &lq_sta->lq, CMD_ASYNC, false);
}