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
typedef  int u8 ;

/* Variables and functions */
 int DID_ABORT ; 
 int DID_BUS_BUSY ; 
 int DID_ERROR ; 
 int DID_NO_CONNECT ; 
 int DID_OK ; 
 int DID_RESET ; 
#define  RS_ABORTED 136 
#define  RS_BUSY 135 
#define  RS_OVERRUN 134 
#define  RS_RESET 133 
#define  RS_SCSI_ERROR 132 
#define  RS_SEL 131 
#define  RS_SEL2 130 
#define  RS_SUCCESS 129 
#define  RS_UNDERRUN 128 

int esas2r_req_status_to_error(u8 req_stat)
{
	switch (req_stat) {
	case RS_OVERRUN:
	case RS_UNDERRUN:
	case RS_SUCCESS:
	/*
	 * NOTE: SCSI mid-layer wants a good status for a SCSI error, because
	 *       it will check the scsi_stat value in the completion anyway.
	 */
	case RS_SCSI_ERROR:
		return DID_OK;

	case RS_SEL:
	case RS_SEL2:
		return DID_NO_CONNECT;

	case RS_RESET:
		return DID_RESET;

	case RS_ABORTED:
		return DID_ABORT;

	case RS_BUSY:
		return DID_BUS_BUSY;
	}

	/* everything else is just an error. */

	return DID_ERROR;
}