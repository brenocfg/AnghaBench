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
struct sbp_target_agent {int dummy; } ;
struct fw_card {int dummy; } ;

/* Variables and functions */
 int RCODE_COMPLETE ; 
 int RCODE_TYPE_ERROR ; 
#define  TCODE_READ_QUADLET_REQUEST 129 
#define  TCODE_WRITE_QUADLET_REQUEST 128 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int tgt_agent_rw_unsolicited_status_enable(struct fw_card *card,
		int tcode, void *data, struct sbp_target_agent *agent)
{
	switch (tcode) {
	case TCODE_WRITE_QUADLET_REQUEST:
		pr_debug("tgt_agent UNSOLICITED_STATUS_ENABLE\n");
		/* ignored as we don't send unsolicited status */
		return RCODE_COMPLETE;

	case TCODE_READ_QUADLET_REQUEST:
		return RCODE_COMPLETE;

	default:
		return RCODE_TYPE_ERROR;
	}
}