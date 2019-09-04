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
typedef  int uint8_t ;
typedef  int int8_t ;
typedef  int /*<<< orphan*/  USBD_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  INVALID_CDB ; 
#define  SCSI_ALLOW_MEDIUM_REMOVAL 141 
 int SCSI_AllowMediumRemoval (int /*<<< orphan*/ *,int,int*) ; 
#define  SCSI_INQUIRY 140 
 int SCSI_Inquiry (int /*<<< orphan*/ *,int,int*) ; 
#define  SCSI_MODE_SENSE10 139 
#define  SCSI_MODE_SENSE6 138 
 int SCSI_ModeSense10 (int /*<<< orphan*/ *,int,int*) ; 
 int SCSI_ModeSense6 (int /*<<< orphan*/ *,int,int*) ; 
#define  SCSI_READ10 137 
#define  SCSI_READ_CAPACITY10 136 
#define  SCSI_READ_FORMAT_CAPACITIES 135 
#define  SCSI_REQUEST_SENSE 134 
 int SCSI_Read10 (int /*<<< orphan*/ *,int,int*) ; 
 int SCSI_ReadCapacity10 (int /*<<< orphan*/ *,int,int*) ; 
 int SCSI_ReadFormatCapacity (int /*<<< orphan*/ *,int,int*) ; 
 int SCSI_RequestSense (int /*<<< orphan*/ *,int,int*) ; 
#define  SCSI_START_STOP_UNIT 133 
#define  SCSI_SYNCHRONIZE_CACHE10 132 
#define  SCSI_SYNCHRONIZE_CACHE16 131 
 int /*<<< orphan*/  SCSI_SenseCode (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SCSI_StartStopUnit (int /*<<< orphan*/ *,int,int*) ; 
 int SCSI_SynchronizeCache (int /*<<< orphan*/ *,int,int*) ; 
#define  SCSI_TEST_UNIT_READY 130 
 int SCSI_TestUnitReady (int /*<<< orphan*/ *,int,int*) ; 
#define  SCSI_VERIFY10 129 
 int SCSI_Verify10 (int /*<<< orphan*/ *,int,int*) ; 
#define  SCSI_WRITE10 128 
 int SCSI_Write10 (int /*<<< orphan*/ *,int,int*) ; 

int8_t SCSI_ProcessCmd(USBD_HandleTypeDef  *pdev,
                           uint8_t lun,
                           uint8_t *params)
{
    /*
    if (params[0] != SCSI_READ10 && params[0] != SCSI_WRITE10) {
        printf("SCSI_ProcessCmd(lun=%d, params=%x, %x)\n", lun, params[0], params[1]);
    }
    */

  switch (params[0])
  {
  case SCSI_TEST_UNIT_READY:
    return SCSI_TestUnitReady(pdev, lun, params);

  case SCSI_REQUEST_SENSE:
    return SCSI_RequestSense (pdev, lun, params);
  case SCSI_INQUIRY:
    return SCSI_Inquiry(pdev, lun, params);

  case SCSI_START_STOP_UNIT:
    return SCSI_StartStopUnit(pdev, lun, params);

  case SCSI_ALLOW_MEDIUM_REMOVAL:
    return SCSI_AllowMediumRemoval(pdev, lun, params);

  case SCSI_MODE_SENSE6:
    return SCSI_ModeSense6 (pdev, lun, params);

  case SCSI_MODE_SENSE10:
    return SCSI_ModeSense10 (pdev, lun, params);

  case SCSI_SYNCHRONIZE_CACHE10:
  case SCSI_SYNCHRONIZE_CACHE16:
    return SCSI_SynchronizeCache(pdev, lun, params);

  case SCSI_READ_FORMAT_CAPACITIES:
    return SCSI_ReadFormatCapacity(pdev, lun, params);

  case SCSI_READ_CAPACITY10:
    return SCSI_ReadCapacity10(pdev, lun, params);

  case SCSI_READ10:
    return SCSI_Read10(pdev, lun, params);

  case SCSI_WRITE10:
    return SCSI_Write10(pdev, lun, params);

  case SCSI_VERIFY10:
    return SCSI_Verify10(pdev, lun, params);

  default:
    SCSI_SenseCode(pdev,
                   lun,
                   ILLEGAL_REQUEST,
                   INVALID_CDB);
    return -1;
  }
}