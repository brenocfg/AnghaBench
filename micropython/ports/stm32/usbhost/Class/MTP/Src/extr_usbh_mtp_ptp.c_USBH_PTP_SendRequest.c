#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_11__ {TYPE_1__* pActiveClass; } ;
typedef  TYPE_3__ USBH_HandleTypeDef ;
struct TYPE_14__ {int /*<<< orphan*/  param5; int /*<<< orphan*/  param4; int /*<<< orphan*/  param3; int /*<<< orphan*/  param2; int /*<<< orphan*/  param1; int /*<<< orphan*/  trans_id; int /*<<< orphan*/  code; int /*<<< orphan*/  type; scalar_t__ length; } ;
struct TYPE_10__ {TYPE_6__ op_container; } ;
struct TYPE_13__ {TYPE_2__ ptp; } ;
struct TYPE_12__ {int Nparam; int /*<<< orphan*/  Param5; int /*<<< orphan*/  Param4; int /*<<< orphan*/  Param3; int /*<<< orphan*/  Param2; int /*<<< orphan*/  Param1; int /*<<< orphan*/  Transaction_ID; int /*<<< orphan*/  Code; } ;
struct TYPE_9__ {TYPE_5__* pData; } ;
typedef  int /*<<< orphan*/  PTP_OpContainerTypedef ;
typedef  TYPE_4__ PTP_ContainerTypedef ;
typedef  TYPE_5__ MTP_HandleTypeDef ;

/* Variables and functions */
 scalar_t__ PTP_USB_BULK_REQ_LEN ; 
 int /*<<< orphan*/  PTP_USB_CONTAINER_COMMAND ; 
 int /*<<< orphan*/  USBH_OK ; 
 int /*<<< orphan*/  USBH_memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 

USBH_StatusTypeDef USBH_PTP_SendRequest (USBH_HandleTypeDef *phost, PTP_ContainerTypedef  *req)
{
  USBH_StatusTypeDef            status = USBH_OK; 
  MTP_HandleTypeDef             *MTP_Handle =  phost->pActiveClass->pData; 
  
  /* Clear PTP Data container*/
  USBH_memset(&(MTP_Handle->ptp.op_container), 0, sizeof(PTP_OpContainerTypedef));
  
  /* build appropriate USB container */
  MTP_Handle->ptp.op_container.length = PTP_USB_BULK_REQ_LEN- (sizeof(uint32_t)*(5-req->Nparam));
  MTP_Handle->ptp.op_container.type = PTP_USB_CONTAINER_COMMAND;
  MTP_Handle->ptp.op_container.code = req->Code;
  MTP_Handle->ptp.op_container.trans_id = req->Transaction_ID;
  MTP_Handle->ptp.op_container.param1 = req->Param1;
  MTP_Handle->ptp.op_container.param2 = req->Param2;
  MTP_Handle->ptp.op_container.param3 = req->Param3;
  MTP_Handle->ptp.op_container.param4 = req->Param4;
  MTP_Handle->ptp.op_container.param5 = req->Param5;
  
  return status;
}