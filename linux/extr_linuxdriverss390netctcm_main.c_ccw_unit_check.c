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
struct channel {int sense_rc; int /*<<< orphan*/  fsm; int /*<<< orphan*/  id; } ;
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  CTCM_DBF_TEXT_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  CTCM_FUNTAIL ; 
 int /*<<< orphan*/  CTC_DBF_DEBUG ; 
 int /*<<< orphan*/  CTC_DBF_WARN ; 
 int /*<<< orphan*/  CTC_EVENT_UC_HWFAIL ; 
 int /*<<< orphan*/  CTC_EVENT_UC_RCRESET ; 
 int /*<<< orphan*/  CTC_EVENT_UC_RSRESET ; 
 int /*<<< orphan*/  CTC_EVENT_UC_RXPARITY ; 
 int /*<<< orphan*/  CTC_EVENT_UC_TXPARITY ; 
 int /*<<< orphan*/  CTC_EVENT_UC_TXTIMEOUT ; 
 int /*<<< orphan*/  CTC_EVENT_UC_UNKNOWN ; 
 int /*<<< orphan*/  CTC_EVENT_UC_ZERO ; 
 int SNS0_BUS_OUT_CHECK ; 
 int SNS0_CMD_REJECT ; 
 int SNS0_EQUIPMENT_CHECK ; 
 int SNS0_INTERVENTION_REQ ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  fsm_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct channel*) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccw_unit_check(struct channel *ch, __u8 sense)
{
	CTCM_DBF_TEXT_(TRACE, CTC_DBF_DEBUG,
			"%s(%s): %02x",
				CTCM_FUNTAIL, ch->id, sense);

	if (sense & SNS0_INTERVENTION_REQ) {
		if (sense & 0x01) {
			if (ch->sense_rc != 0x01) {
				pr_notice(
					"%s: The communication peer has "
					"disconnected\n", ch->id);
				ch->sense_rc = 0x01;
			}
			fsm_event(ch->fsm, CTC_EVENT_UC_RCRESET, ch);
		} else {
			if (ch->sense_rc != SNS0_INTERVENTION_REQ) {
				pr_notice(
					"%s: The remote operating system is "
					"not available\n", ch->id);
				ch->sense_rc = SNS0_INTERVENTION_REQ;
			}
			fsm_event(ch->fsm, CTC_EVENT_UC_RSRESET, ch);
		}
	} else if (sense & SNS0_EQUIPMENT_CHECK) {
		if (sense & SNS0_BUS_OUT_CHECK) {
			if (ch->sense_rc != SNS0_BUS_OUT_CHECK) {
				CTCM_DBF_TEXT_(TRACE, CTC_DBF_WARN,
					"%s(%s): remote HW error %02x",
						CTCM_FUNTAIL, ch->id, sense);
				ch->sense_rc = SNS0_BUS_OUT_CHECK;
			}
			fsm_event(ch->fsm, CTC_EVENT_UC_HWFAIL, ch);
		} else {
			if (ch->sense_rc != SNS0_EQUIPMENT_CHECK) {
				CTCM_DBF_TEXT_(TRACE, CTC_DBF_WARN,
					"%s(%s): remote read parity error %02x",
						CTCM_FUNTAIL, ch->id, sense);
				ch->sense_rc = SNS0_EQUIPMENT_CHECK;
			}
			fsm_event(ch->fsm, CTC_EVENT_UC_RXPARITY, ch);
		}
	} else if (sense & SNS0_BUS_OUT_CHECK) {
		if (ch->sense_rc != SNS0_BUS_OUT_CHECK) {
			CTCM_DBF_TEXT_(TRACE, CTC_DBF_WARN,
				"%s(%s): BUS OUT error %02x",
					CTCM_FUNTAIL, ch->id, sense);
			ch->sense_rc = SNS0_BUS_OUT_CHECK;
		}
		if (sense & 0x04)	/* data-streaming timeout */
			fsm_event(ch->fsm, CTC_EVENT_UC_TXTIMEOUT, ch);
		else			/* Data-transfer parity error */
			fsm_event(ch->fsm, CTC_EVENT_UC_TXPARITY, ch);
	} else if (sense & SNS0_CMD_REJECT) {
		if (ch->sense_rc != SNS0_CMD_REJECT) {
			CTCM_DBF_TEXT_(TRACE, CTC_DBF_WARN,
				"%s(%s): Command rejected",
						CTCM_FUNTAIL, ch->id);
			ch->sense_rc = SNS0_CMD_REJECT;
		}
	} else if (sense == 0) {
		CTCM_DBF_TEXT_(TRACE, CTC_DBF_WARN,
			"%s(%s): Unit check ZERO",
					CTCM_FUNTAIL, ch->id);
		fsm_event(ch->fsm, CTC_EVENT_UC_ZERO, ch);
	} else {
		CTCM_DBF_TEXT_(TRACE, CTC_DBF_WARN,
			"%s(%s): Unit check code %02x unknown",
					CTCM_FUNTAIL, ch->id, sense);
		fsm_event(ch->fsm, CTC_EVENT_UC_UNKNOWN, ch);
	}
}