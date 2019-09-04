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
struct scsi_cmnd {int* cmnd; } ;
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
#define  ADD_BATCHCMD 131 
#define  GET_BATCHRSP 130 
#define  INIT_BATCHCMD 129 
#define  SEND_BATCHCMD 128 
 int TRANSPORT_ERROR ; 
 int rw_mem_cmd_buf (struct scsi_cmnd*,struct rtsx_chip*) ; 

__attribute__((used)) static int suit_cmd(struct scsi_cmnd *srb, struct rtsx_chip *chip)
{
	switch (srb->cmnd[3]) {
	case INIT_BATCHCMD:
	case ADD_BATCHCMD:
	case SEND_BATCHCMD:
	case GET_BATCHRSP:
		return rw_mem_cmd_buf(srb, chip);
	default:
		return TRANSPORT_ERROR;
	}
}