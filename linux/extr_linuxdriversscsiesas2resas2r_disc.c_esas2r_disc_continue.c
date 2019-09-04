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
struct esas2r_request {int /*<<< orphan*/ * interrupt_cx; } ;
struct esas2r_disc_context {int flags; int state; } ;
struct esas2r_adapter {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_DISC_IN_PROG ; 
 int /*<<< orphan*/  AF_DISC_PENDING ; 
 int DCF_DEV_CHANGE ; 
 int DCF_DEV_SCAN ; 
#define  DCS_BLOCK_DEV_SCAN 135 
#define  DCS_DEV_ADD 134 
#define  DCS_DEV_RMV 133 
#define  DCS_DISC_DONE 132 
#define  DCS_PART_INFO 131 
#define  DCS_PT_DEV_ADDR 130 
#define  DCS_PT_DEV_INFO 129 
#define  DCS_RAID_GRP_INFO 128 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esas2r_bugon () ; 
 int esas2r_disc_block_dev_scan (struct esas2r_adapter*,struct esas2r_request*) ; 
 int esas2r_disc_dev_add (struct esas2r_adapter*,struct esas2r_request*) ; 
 int esas2r_disc_dev_remove (struct esas2r_adapter*,struct esas2r_request*) ; 
 int /*<<< orphan*/  esas2r_disc_fix_curr_requests (struct esas2r_adapter*) ; 
 int esas2r_disc_part_info (struct esas2r_adapter*,struct esas2r_request*) ; 
 int esas2r_disc_passthru_dev_addr (struct esas2r_adapter*,struct esas2r_request*) ; 
 int esas2r_disc_passthru_dev_info (struct esas2r_adapter*,struct esas2r_request*) ; 
 int esas2r_disc_raid_grp_info (struct esas2r_adapter*,struct esas2r_request*) ; 
 int esas2r_disc_start_port (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool esas2r_disc_continue(struct esas2r_adapter *a,
				 struct esas2r_request *rq)
{
	struct esas2r_disc_context *dc =
		(struct esas2r_disc_context *)rq->interrupt_cx;
	bool rslt;

	/* Device discovery/removal */
	while (dc->flags & (DCF_DEV_CHANGE | DCF_DEV_SCAN)) {
		rslt = false;

		switch (dc->state) {
		case DCS_DEV_RMV:

			rslt = esas2r_disc_dev_remove(a, rq);
			break;

		case DCS_DEV_ADD:

			rslt = esas2r_disc_dev_add(a, rq);
			break;

		case DCS_BLOCK_DEV_SCAN:

			rslt = esas2r_disc_block_dev_scan(a, rq);
			break;

		case DCS_RAID_GRP_INFO:

			rslt = esas2r_disc_raid_grp_info(a, rq);
			break;

		case DCS_PART_INFO:

			rslt = esas2r_disc_part_info(a, rq);
			break;

		case DCS_PT_DEV_INFO:

			rslt = esas2r_disc_passthru_dev_info(a, rq);
			break;
		case DCS_PT_DEV_ADDR:

			rslt = esas2r_disc_passthru_dev_addr(a, rq);
			break;
		case DCS_DISC_DONE:

			dc->flags &= ~(DCF_DEV_CHANGE | DCF_DEV_SCAN);
			break;

		default:

			esas2r_bugon();
			dc->state = DCS_DISC_DONE;
			break;
		}

		if (rslt)
			return true;
	}

	/* Discovery is done...for now. */
	rq->interrupt_cx = NULL;

	if (!test_bit(AF_DISC_PENDING, &a->flags))
		esas2r_disc_fix_curr_requests(a);

	clear_bit(AF_DISC_IN_PROG, &a->flags);

	/* Start the next discovery. */
	return esas2r_disc_start_port(a);
}