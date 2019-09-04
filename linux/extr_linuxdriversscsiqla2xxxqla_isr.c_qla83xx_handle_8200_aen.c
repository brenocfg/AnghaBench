#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_7__ {int nic_core_hung; scalar_t__ nic_core_reset_owner; } ;
struct qla_hw_data {TYPE_1__ flags; } ;
struct TYPE_8__ {struct qla_hw_data* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;

/* Variables and functions */
 int ERR_LEVEL_NON_FATAL ; 
 int ERR_LEVEL_RECOVERABLE_FATAL ; 
 int ERR_LEVEL_UNRECOVERABLE_FATAL ; 
 int IDC_DEVICE_STATE_CHANGE ; 
 int IDC_HEARTBEAT_FAILURE ; 
 int IDC_NIC_FW_REPORTED_FAILURE ; 
 int IDC_PEG_HALT_STATUS_CHANGE ; 
 int /*<<< orphan*/  MBA_IDC_AEN ; 
 int /*<<< orphan*/  QLA83XX_NIC_CORE_RESET ; 
 int /*<<< orphan*/  QLA83XX_NIC_CORE_UNRECOVERABLE ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_2__*,int,char*,int,int,int,int) ; 
 int /*<<< orphan*/  ql_dbg_async ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_2__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_fatal ; 
 int /*<<< orphan*/  ql_log_info ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla83xx_schedule_work (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qla83xx_handle_8200_aen(scsi_qla_host_t *vha, uint16_t *mb)
{
	struct qla_hw_data *ha = vha->hw;

	/*
	 * 8200 AEN Interpretation:
	 * mb[0] = AEN code
	 * mb[1] = AEN Reason code
	 * mb[2] = LSW of Peg-Halt Status-1 Register
	 * mb[6] = MSW of Peg-Halt Status-1 Register
	 * mb[3] = LSW of Peg-Halt Status-2 register
	 * mb[7] = MSW of Peg-Halt Status-2 register
	 * mb[4] = IDC Device-State Register value
	 * mb[5] = IDC Driver-Presence Register value
	 */
	ql_dbg(ql_dbg_async, vha, 0x506b, "AEN Code: mb[0] = 0x%x AEN reason: "
	    "mb[1] = 0x%x PH-status1: mb[2] = 0x%x PH-status1: mb[6] = 0x%x.\n",
	    mb[0], mb[1], mb[2], mb[6]);
	ql_dbg(ql_dbg_async, vha, 0x506c, "PH-status2: mb[3] = 0x%x "
	    "PH-status2: mb[7] = 0x%x Device-State: mb[4] = 0x%x "
	    "Drv-Presence: mb[5] = 0x%x.\n", mb[3], mb[7], mb[4], mb[5]);

	if (mb[1] & (IDC_PEG_HALT_STATUS_CHANGE | IDC_NIC_FW_REPORTED_FAILURE |
				IDC_HEARTBEAT_FAILURE)) {
		ha->flags.nic_core_hung = 1;
		ql_log(ql_log_warn, vha, 0x5060,
		    "83XX: F/W Error Reported: Check if reset required.\n");

		if (mb[1] & IDC_PEG_HALT_STATUS_CHANGE) {
			uint32_t protocol_engine_id, fw_err_code, err_level;

			/*
			 * IDC_PEG_HALT_STATUS_CHANGE interpretation:
			 *  - PEG-Halt Status-1 Register:
			 *	(LSW = mb[2], MSW = mb[6])
			 *	Bits 0-7   = protocol-engine ID
			 *	Bits 8-28  = f/w error code
			 *	Bits 29-31 = Error-level
			 *	    Error-level 0x1 = Non-Fatal error
			 *	    Error-level 0x2 = Recoverable Fatal error
			 *	    Error-level 0x4 = UnRecoverable Fatal error
			 *  - PEG-Halt Status-2 Register:
			 *	(LSW = mb[3], MSW = mb[7])
			 */
			protocol_engine_id = (mb[2] & 0xff);
			fw_err_code = (((mb[2] & 0xff00) >> 8) |
			    ((mb[6] & 0x1fff) << 8));
			err_level = ((mb[6] & 0xe000) >> 13);
			ql_log(ql_log_warn, vha, 0x5061, "PegHalt Status-1 "
			    "Register: protocol_engine_id=0x%x "
			    "fw_err_code=0x%x err_level=0x%x.\n",
			    protocol_engine_id, fw_err_code, err_level);
			ql_log(ql_log_warn, vha, 0x5062, "PegHalt Status-2 "
			    "Register: 0x%x%x.\n", mb[7], mb[3]);
			if (err_level == ERR_LEVEL_NON_FATAL) {
				ql_log(ql_log_warn, vha, 0x5063,
				    "Not a fatal error, f/w has recovered itself.\n");
			} else if (err_level == ERR_LEVEL_RECOVERABLE_FATAL) {
				ql_log(ql_log_fatal, vha, 0x5064,
				    "Recoverable Fatal error: Chip reset "
				    "required.\n");
				qla83xx_schedule_work(vha,
				    QLA83XX_NIC_CORE_RESET);
			} else if (err_level == ERR_LEVEL_UNRECOVERABLE_FATAL) {
				ql_log(ql_log_fatal, vha, 0x5065,
				    "Unrecoverable Fatal error: Set FAILED "
				    "state, reboot required.\n");
				qla83xx_schedule_work(vha,
				    QLA83XX_NIC_CORE_UNRECOVERABLE);
			}
		}

		if (mb[1] & IDC_NIC_FW_REPORTED_FAILURE) {
			uint16_t peg_fw_state, nw_interface_link_up;
			uint16_t nw_interface_signal_detect, sfp_status;
			uint16_t htbt_counter, htbt_monitor_enable;
			uint16_t sfp_additional_info, sfp_multirate;
			uint16_t sfp_tx_fault, link_speed, dcbx_status;

			/*
			 * IDC_NIC_FW_REPORTED_FAILURE interpretation:
			 *  - PEG-to-FC Status Register:
			 *	(LSW = mb[2], MSW = mb[6])
			 *	Bits 0-7   = Peg-Firmware state
			 *	Bit 8      = N/W Interface Link-up
			 *	Bit 9      = N/W Interface signal detected
			 *	Bits 10-11 = SFP Status
			 *	  SFP Status 0x0 = SFP+ transceiver not expected
			 *	  SFP Status 0x1 = SFP+ transceiver not present
			 *	  SFP Status 0x2 = SFP+ transceiver invalid
			 *	  SFP Status 0x3 = SFP+ transceiver present and
			 *	  valid
			 *	Bits 12-14 = Heartbeat Counter
			 *	Bit 15     = Heartbeat Monitor Enable
			 *	Bits 16-17 = SFP Additional Info
			 *	  SFP info 0x0 = Unregocnized transceiver for
			 *	  Ethernet
			 *	  SFP info 0x1 = SFP+ brand validation failed
			 *	  SFP info 0x2 = SFP+ speed validation failed
			 *	  SFP info 0x3 = SFP+ access error
			 *	Bit 18     = SFP Multirate
			 *	Bit 19     = SFP Tx Fault
			 *	Bits 20-22 = Link Speed
			 *	Bits 23-27 = Reserved
			 *	Bits 28-30 = DCBX Status
			 *	  DCBX Status 0x0 = DCBX Disabled
			 *	  DCBX Status 0x1 = DCBX Enabled
			 *	  DCBX Status 0x2 = DCBX Exchange error
			 *	Bit 31     = Reserved
			 */
			peg_fw_state = (mb[2] & 0x00ff);
			nw_interface_link_up = ((mb[2] & 0x0100) >> 8);
			nw_interface_signal_detect = ((mb[2] & 0x0200) >> 9);
			sfp_status = ((mb[2] & 0x0c00) >> 10);
			htbt_counter = ((mb[2] & 0x7000) >> 12);
			htbt_monitor_enable = ((mb[2] & 0x8000) >> 15);
			sfp_additional_info = (mb[6] & 0x0003);
			sfp_multirate = ((mb[6] & 0x0004) >> 2);
			sfp_tx_fault = ((mb[6] & 0x0008) >> 3);
			link_speed = ((mb[6] & 0x0070) >> 4);
			dcbx_status = ((mb[6] & 0x7000) >> 12);

			ql_log(ql_log_warn, vha, 0x5066,
			    "Peg-to-Fc Status Register:\n"
			    "peg_fw_state=0x%x, nw_interface_link_up=0x%x, "
			    "nw_interface_signal_detect=0x%x"
			    "\nsfp_statis=0x%x.\n ", peg_fw_state,
			    nw_interface_link_up, nw_interface_signal_detect,
			    sfp_status);
			ql_log(ql_log_warn, vha, 0x5067,
			    "htbt_counter=0x%x, htbt_monitor_enable=0x%x, "
			    "sfp_additional_info=0x%x, sfp_multirate=0x%x.\n ",
			    htbt_counter, htbt_monitor_enable,
			    sfp_additional_info, sfp_multirate);
			ql_log(ql_log_warn, vha, 0x5068,
			    "sfp_tx_fault=0x%x, link_state=0x%x, "
			    "dcbx_status=0x%x.\n", sfp_tx_fault, link_speed,
			    dcbx_status);

			qla83xx_schedule_work(vha, QLA83XX_NIC_CORE_RESET);
		}

		if (mb[1] & IDC_HEARTBEAT_FAILURE) {
			ql_log(ql_log_warn, vha, 0x5069,
			    "Heartbeat Failure encountered, chip reset "
			    "required.\n");

			qla83xx_schedule_work(vha, QLA83XX_NIC_CORE_RESET);
		}
	}

	if (mb[1] & IDC_DEVICE_STATE_CHANGE) {
		ql_log(ql_log_info, vha, 0x506a,
		    "IDC Device-State changed = 0x%x.\n", mb[4]);
		if (ha->flags.nic_core_reset_owner)
			return;
		qla83xx_schedule_work(vha, MBA_IDC_AEN);
	}
}