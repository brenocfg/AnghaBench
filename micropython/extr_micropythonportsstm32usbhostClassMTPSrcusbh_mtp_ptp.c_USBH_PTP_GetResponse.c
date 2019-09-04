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
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_12__ {TYPE_1__* pActiveClass; } ;
typedef  TYPE_4__ USBH_HandleTypeDef ;
struct TYPE_10__ {int /*<<< orphan*/  param5; int /*<<< orphan*/  param4; int /*<<< orphan*/  param3; int /*<<< orphan*/  param2; int /*<<< orphan*/  param1; int /*<<< orphan*/  trans_id; int /*<<< orphan*/  code; } ;
struct TYPE_11__ {TYPE_2__ resp_container; int /*<<< orphan*/  session_id; } ;
struct TYPE_14__ {TYPE_3__ ptp; } ;
struct TYPE_13__ {int /*<<< orphan*/  Param5; int /*<<< orphan*/  Param4; int /*<<< orphan*/  Param3; int /*<<< orphan*/  Param2; int /*<<< orphan*/  Param1; int /*<<< orphan*/  Transaction_ID; int /*<<< orphan*/  SessionID; int /*<<< orphan*/  Code; } ;
struct TYPE_9__ {TYPE_6__* pData; } ;
typedef  TYPE_5__ PTP_ContainerTypedef ;
typedef  TYPE_6__ MTP_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USBH_OK ; 

USBH_StatusTypeDef USBH_PTP_GetResponse (USBH_HandleTypeDef *phost, PTP_ContainerTypedef  *resp)
{
  USBH_StatusTypeDef            status = USBH_OK; 
  MTP_HandleTypeDef             *MTP_Handle =  phost->pActiveClass->pData; 
      
  /* build an appropriate PTPContainer */
  resp->Code = MTP_Handle->ptp.resp_container.code;
  resp->SessionID = MTP_Handle->ptp.session_id;
  resp->Transaction_ID = MTP_Handle->ptp.resp_container.trans_id;
  resp->Param1 = MTP_Handle->ptp.resp_container.param1;
  resp->Param2 = MTP_Handle->ptp.resp_container.param2;
  resp->Param3 = MTP_Handle->ptp.resp_container.param3;
  resp->Param4 = MTP_Handle->ptp.resp_container.param4;
  resp->Param5 = MTP_Handle->ptp.resp_container.param5;
  
  return status;
}