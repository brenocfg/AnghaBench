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
typedef  scalar_t__ u_int ;
struct scb {TYPE_1__* hscb; } ;
struct ahc_softc {int dummy; } ;
typedef  int /*<<< orphan*/  role_t ;
struct TYPE_2__ {scalar_t__ tag; } ;

/* Variables and functions */
 char ALL_CHANNELS ; 
 int CAM_LUN_WILDCARD ; 
 int CAM_TARGET_WILDCARD ; 
 char SCB_GET_CHANNEL (struct ahc_softc*,struct scb*) ; 
 int SCB_GET_LUN (struct scb*) ; 
 int SCB_GET_TARGET (struct ahc_softc*,struct scb*) ; 
 scalar_t__ SCB_LIST_NULL ; 

int
ahc_match_scb(struct ahc_softc *ahc, struct scb *scb, int target,
	      char channel, int lun, u_int tag, role_t role)
{
	int targ = SCB_GET_TARGET(ahc, scb);
	char chan = SCB_GET_CHANNEL(ahc, scb);
	int slun = SCB_GET_LUN(scb);
	int match;

	match = ((chan == channel) || (channel == ALL_CHANNELS));
	if (match != 0)
		match = ((targ == target) || (target == CAM_TARGET_WILDCARD));
	if (match != 0)
		match = ((lun == slun) || (lun == CAM_LUN_WILDCARD));
	if (match != 0) {
#ifdef AHC_TARGET_MODE
		int group;

		group = XPT_FC_GROUP(scb->io_ctx->ccb_h.func_code);
		if (role == ROLE_INITIATOR) {
			match = (group != XPT_FC_GROUP_TMODE)
			      && ((tag == scb->hscb->tag)
			       || (tag == SCB_LIST_NULL));
		} else if (role == ROLE_TARGET) {
			match = (group == XPT_FC_GROUP_TMODE)
			      && ((tag == scb->io_ctx->csio.tag_id)
			       || (tag == SCB_LIST_NULL));
		}
#else /* !AHC_TARGET_MODE */
		match = ((tag == scb->hscb->tag) || (tag == SCB_LIST_NULL));
#endif /* AHC_TARGET_MODE */
	}

	return match;
}