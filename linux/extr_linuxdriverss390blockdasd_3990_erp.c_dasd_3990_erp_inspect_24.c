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
struct dasd_ccw_req {int dummy; } ;

/* Variables and functions */
 char SNS0_BUS_OUT_CHECK ; 
 char SNS0_CMD_REJECT ; 
 char SNS0_DATA_CHECK ; 
 char SNS0_EQUIPMENT_CHECK ; 
 char SNS0_INTERVENTION_REQ ; 
 char SNS0_OVERRUN ; 
 char SNS1_EOC ; 
 char SNS1_FILE_PROTECTED ; 
 char SNS1_INV_TRACK_FORMAT ; 
 char SNS1_NO_REC_FOUND ; 
 char SNS2_ENV_DATA_PRESENT ; 
 struct dasd_ccw_req* dasd_3990_erp_EOC (struct dasd_ccw_req*,char*) ; 
 struct dasd_ccw_req* dasd_3990_erp_bus_out (struct dasd_ccw_req*) ; 
 struct dasd_ccw_req* dasd_3990_erp_com_rej (struct dasd_ccw_req*,char*) ; 
 struct dasd_ccw_req* dasd_3990_erp_data_check (struct dasd_ccw_req*,char*) ; 
 struct dasd_ccw_req* dasd_3990_erp_env_data (struct dasd_ccw_req*,char*) ; 
 struct dasd_ccw_req* dasd_3990_erp_equip_check (struct dasd_ccw_req*,char*) ; 
 struct dasd_ccw_req* dasd_3990_erp_file_prot (struct dasd_ccw_req*) ; 
 struct dasd_ccw_req* dasd_3990_erp_int_req (struct dasd_ccw_req*) ; 
 struct dasd_ccw_req* dasd_3990_erp_inv_format (struct dasd_ccw_req*,char*) ; 
 struct dasd_ccw_req* dasd_3990_erp_no_rec (struct dasd_ccw_req*,char*) ; 
 struct dasd_ccw_req* dasd_3990_erp_overrun (struct dasd_ccw_req*,char*) ; 

__attribute__((used)) static struct dasd_ccw_req *
dasd_3990_erp_inspect_24(struct dasd_ccw_req * erp, char *sense)
{

	struct dasd_ccw_req *erp_filled = NULL;

	/* Check sense for ....	   */
	/* 'Command Reject'	   */
	if ((erp_filled == NULL) && (sense[0] & SNS0_CMD_REJECT)) {
		erp_filled = dasd_3990_erp_com_rej(erp, sense);
	}
	/* 'Intervention Required' */
	if ((erp_filled == NULL) && (sense[0] & SNS0_INTERVENTION_REQ)) {
		erp_filled = dasd_3990_erp_int_req(erp);
	}
	/* 'Bus Out Parity Check'  */
	if ((erp_filled == NULL) && (sense[0] & SNS0_BUS_OUT_CHECK)) {
		erp_filled = dasd_3990_erp_bus_out(erp);
	}
	/* 'Equipment Check'	   */
	if ((erp_filled == NULL) && (sense[0] & SNS0_EQUIPMENT_CHECK)) {
		erp_filled = dasd_3990_erp_equip_check(erp, sense);
	}
	/* 'Data Check'		   */
	if ((erp_filled == NULL) && (sense[0] & SNS0_DATA_CHECK)) {
		erp_filled = dasd_3990_erp_data_check(erp, sense);
	}
	/* 'Overrun'		   */
	if ((erp_filled == NULL) && (sense[0] & SNS0_OVERRUN)) {
		erp_filled = dasd_3990_erp_overrun(erp, sense);
	}
	/* 'Invalid Track Format'  */
	if ((erp_filled == NULL) && (sense[1] & SNS1_INV_TRACK_FORMAT)) {
		erp_filled = dasd_3990_erp_inv_format(erp, sense);
	}
	/* 'End-of-Cylinder'	   */
	if ((erp_filled == NULL) && (sense[1] & SNS1_EOC)) {
		erp_filled = dasd_3990_erp_EOC(erp, sense);
	}
	/* 'Environmental Data'	   */
	if ((erp_filled == NULL) && (sense[2] & SNS2_ENV_DATA_PRESENT)) {
		erp_filled = dasd_3990_erp_env_data(erp, sense);
	}
	/* 'No Record Found'	   */
	if ((erp_filled == NULL) && (sense[1] & SNS1_NO_REC_FOUND)) {
		erp_filled = dasd_3990_erp_no_rec(erp, sense);
	}
	/* 'File Protected'	   */
	if ((erp_filled == NULL) && (sense[1] & SNS1_FILE_PROTECTED)) {
		erp_filled = dasd_3990_erp_file_prot(erp);
	}
	/* other (unknown) error - do default ERP */
	if (erp_filled == NULL) {

		erp_filled = erp;
	}

	return erp_filled;

}