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
typedef  scalar_t__ uint32_t ;
struct scsi_qla_host {int dummy; } ;
struct qla4_83xx_reset_entry_hdr {scalar_t__ count; scalar_t__ delay; } ;
struct qla4_83xx_poll {int /*<<< orphan*/  test_value; int /*<<< orphan*/  test_mask; } ;
struct qla4_83xx_entry {int /*<<< orphan*/  arg2; int /*<<< orphan*/  arg1; } ;

/* Variables and functions */
 scalar_t__ qla4_83xx_poll_reg (struct scsi_qla_host*,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla4_83xx_rd_reg_indirect (struct scsi_qla_host*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void qla4_83xx_poll_list(struct scsi_qla_host *ha,
				struct qla4_83xx_reset_entry_hdr *p_hdr)
{
	long delay;
	struct qla4_83xx_entry *p_entry;
	struct qla4_83xx_poll *p_poll;
	uint32_t i;
	uint32_t value;

	p_poll = (struct qla4_83xx_poll *)
		 ((char *)p_hdr + sizeof(struct qla4_83xx_reset_entry_hdr));

	/* Entries start after 8 byte qla4_83xx_poll, poll header contains
	 * the test_mask, test_value. */
	p_entry = (struct qla4_83xx_entry *)((char *)p_poll +
					     sizeof(struct qla4_83xx_poll));

	delay = (long)p_hdr->delay;
	if (!delay) {
		for (i = 0; i < p_hdr->count; i++, p_entry++) {
			qla4_83xx_poll_reg(ha, p_entry->arg1, delay,
					   p_poll->test_mask,
					   p_poll->test_value);
		}
	} else {
		for (i = 0; i < p_hdr->count; i++, p_entry++) {
			if (qla4_83xx_poll_reg(ha, p_entry->arg1, delay,
					       p_poll->test_mask,
					       p_poll->test_value)) {
				qla4_83xx_rd_reg_indirect(ha, p_entry->arg1,
							  &value);
				qla4_83xx_rd_reg_indirect(ha, p_entry->arg2,
							  &value);
			}
		}
	}
}