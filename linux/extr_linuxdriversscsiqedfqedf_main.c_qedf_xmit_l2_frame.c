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
struct qedf_rport {int dummy; } ;
struct fc_frame_header {scalar_t__ fh_type; scalar_t__ fh_r_ctl; } ;
struct fc_frame {int dummy; } ;

/* Variables and functions */
#define  ELS_ADISC 128 
 scalar_t__ FC_RCTL_ELS_REQ ; 
 scalar_t__ FC_TYPE_ELS ; 
 struct fc_frame_header* fc_frame_header_get (struct fc_frame*) ; 
 int fc_frame_payload_op (struct fc_frame*) ; 
 int /*<<< orphan*/  qedf_send_adisc (struct qedf_rport*,struct fc_frame*) ; 

__attribute__((used)) static int qedf_xmit_l2_frame(struct qedf_rport *fcport, struct fc_frame *fp)
{
	struct fc_frame_header *fh;
	int rc = 0;

	fh = fc_frame_header_get(fp);
	if ((fh->fh_type == FC_TYPE_ELS) &&
	    (fh->fh_r_ctl == FC_RCTL_ELS_REQ)) {
		switch (fc_frame_payload_op(fp)) {
		case ELS_ADISC:
			qedf_send_adisc(fcport, fp);
			rc = 1;
			break;
		}
	}

	return rc;
}