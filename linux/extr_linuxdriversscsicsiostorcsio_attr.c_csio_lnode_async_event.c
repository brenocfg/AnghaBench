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
struct csio_lnode {int dummy; } ;
typedef  enum csio_ln_fc_evt { ____Placeholder_csio_ln_fc_evt } csio_ln_fc_evt ;

/* Variables and functions */
#define  CSIO_LN_FC_ATTRIB_UPDATE 131 
#define  CSIO_LN_FC_LINKDOWN 130 
#define  CSIO_LN_FC_LINKUP 129 
#define  CSIO_LN_FC_RSCN 128 
 int /*<<< orphan*/  csio_fchost_attr_init (struct csio_lnode*) ; 
 int /*<<< orphan*/  csio_is_npiv_ln (struct csio_lnode*) ; 
 int /*<<< orphan*/  csio_vport_set_state (struct csio_lnode*) ; 

void
csio_lnode_async_event(struct csio_lnode *ln, enum csio_ln_fc_evt fc_evt)
{
	switch (fc_evt) {
	case CSIO_LN_FC_RSCN:
		/* Get payload of rscn from ln */
		/* For each RSCN entry */
			/*
			 * fc_host_post_event(shost,
			 *		      fc_get_event_number(),
			 *		      FCH_EVT_RSCN,
			 *		      rscn_entry);
			 */
		break;
	case CSIO_LN_FC_LINKUP:
		/* send fc_host_post_event */
		/* set vport state */
		if (csio_is_npiv_ln(ln))
			csio_vport_set_state(ln);

		break;
	case CSIO_LN_FC_LINKDOWN:
		/* send fc_host_post_event */
		/* set vport state */
		if (csio_is_npiv_ln(ln))
			csio_vport_set_state(ln);

		break;
	case CSIO_LN_FC_ATTRIB_UPDATE:
		csio_fchost_attr_init(ln);
		break;
	default:
		break;
	}
}