#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USBD_StatusTypeDef ;
struct TYPE_11__ {int bRequest; } ;
typedef  TYPE_1__ USBD_SetupReqTypedef ;
typedef  int /*<<< orphan*/  USBD_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_ClrFeature (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  USBD_CtlError (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  USBD_GetConfig (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  USBD_GetDescriptor (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  USBD_GetStatus (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  USBD_OK ; 
 int /*<<< orphan*/  USBD_SetAddress (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  USBD_SetConfig (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  USBD_SetFeature (int /*<<< orphan*/ *,TYPE_1__*) ; 
#define  USB_REQ_CLEAR_FEATURE 134 
#define  USB_REQ_GET_CONFIGURATION 133 
#define  USB_REQ_GET_DESCRIPTOR 132 
#define  USB_REQ_GET_STATUS 131 
#define  USB_REQ_SET_ADDRESS 130 
#define  USB_REQ_SET_CONFIGURATION 129 
#define  USB_REQ_SET_FEATURE 128 

USBD_StatusTypeDef  USBD_StdDevReq (USBD_HandleTypeDef *pdev , USBD_SetupReqTypedef  *req)
{
  USBD_StatusTypeDef ret = USBD_OK;

  switch (req->bRequest)
  {
  case USB_REQ_GET_DESCRIPTOR:

    USBD_GetDescriptor (pdev, req) ;
    break;

  case USB_REQ_SET_ADDRESS:
    USBD_SetAddress(pdev, req);
    break;

  case USB_REQ_SET_CONFIGURATION:
    USBD_SetConfig (pdev , req);
    break;

  case USB_REQ_GET_CONFIGURATION:
    USBD_GetConfig (pdev , req);
    break;

  case USB_REQ_GET_STATUS:
    USBD_GetStatus (pdev , req);
    break;


  case USB_REQ_SET_FEATURE:
    USBD_SetFeature (pdev , req);
    break;

  case USB_REQ_CLEAR_FEATURE:
    USBD_ClrFeature (pdev , req);
    break;

  default:
    USBD_CtlError(pdev , req);
    break;
  }

  return ret;
}