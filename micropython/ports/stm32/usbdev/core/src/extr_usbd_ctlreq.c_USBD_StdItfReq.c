#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USBD_StatusTypeDef ;
struct TYPE_12__ {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; } ;
typedef  TYPE_2__ USBD_SetupReqTypedef ;
struct TYPE_13__ {int dev_state; TYPE_1__* pClass; } ;
typedef  TYPE_3__ USBD_HandleTypeDef ;
struct TYPE_11__ {int /*<<< orphan*/  (* Setup ) (TYPE_3__*,TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LOBYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_CtlError (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  USBD_CtlSendStatus (TYPE_3__*) ; 
 int /*<<< orphan*/  USBD_MAX_NUM_INTERFACES ; 
 int /*<<< orphan*/  USBD_OK ; 
#define  USBD_STATE_CONFIGURED 128 
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_2__*) ; 

USBD_StatusTypeDef  USBD_StdItfReq (USBD_HandleTypeDef *pdev , USBD_SetupReqTypedef  *req)
{
  USBD_StatusTypeDef ret = USBD_OK;

  switch (pdev->dev_state)
  {
  case USBD_STATE_CONFIGURED:

    if (LOBYTE(req->wIndex) <= USBD_MAX_NUM_INTERFACES)
    {
      pdev->pClass->Setup (pdev, req);

      if((req->wLength == 0)&& (ret == USBD_OK))
      {
         USBD_CtlSendStatus(pdev);
      }
    }
    else
    {
       USBD_CtlError(pdev , req);
    }
    break;

  default:
     USBD_CtlError(pdev , req);
    break;
  }
  return USBD_OK;
}