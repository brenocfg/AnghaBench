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
typedef  int u64 ;
struct pp_ctx {int /*<<< orphan*/  ntb; } ;

/* Variables and functions */
 int ntb_db_set_mask (int /*<<< orphan*/ ,int) ; 
 int ntb_db_valid_mask (int /*<<< orphan*/ ) ; 
 int ntb_msg_count (int /*<<< orphan*/ ) ; 
 int ntb_msg_inbits (int /*<<< orphan*/ ) ; 
 int ntb_msg_outbits (int /*<<< orphan*/ ) ; 
 int ntb_msg_set_mask (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pp_mask_events(struct pp_ctx *pp)
{
	u64 db_mask, msg_mask;
	int ret;

	db_mask = ntb_db_valid_mask(pp->ntb);
	ret = ntb_db_set_mask(pp->ntb, db_mask);
	if (ret)
		return ret;

	/* Skip message events masking if unsupported */
	if (ntb_msg_count(pp->ntb) < 1)
		return 0;

	msg_mask = ntb_msg_outbits(pp->ntb) | ntb_msg_inbits(pp->ntb);
	return ntb_msg_set_mask(pp->ntb, msg_mask);
}