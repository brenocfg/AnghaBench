#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_18__ {int wValue; scalar_t__ wLength; } ;
typedef  TYPE_3__ USBD_SetupReqTypedef ;
struct TYPE_19__ {TYPE_2__* pClass; int /*<<< orphan*/  dev_speed; TYPE_1__* pDesc; } ;
typedef  TYPE_4__ USBD_HandleTypeDef ;
struct TYPE_17__ {scalar_t__ (* GetOtherSpeedConfigDescriptor ) (TYPE_4__*,scalar_t__*) ;scalar_t__ (* GetDeviceQualifierDescriptor ) (TYPE_4__*,scalar_t__*) ;scalar_t__ (* GetFSConfigDescriptor ) (TYPE_4__*,scalar_t__*) ;scalar_t__ (* GetHSConfigDescriptor ) (TYPE_4__*,scalar_t__*) ;} ;
struct TYPE_16__ {int* (* GetDeviceDescriptor ) (TYPE_4__*,scalar_t__*) ;int* (* GetStrDescriptor ) (TYPE_4__*,int,scalar_t__*) ;} ;

/* Variables and functions */
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  USBD_CtlError (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  USBD_CtlSendData (TYPE_4__*,int*,scalar_t__) ; 
 int /*<<< orphan*/  USBD_SPEED_HIGH ; 
#define  USB_DESC_TYPE_CONFIGURATION 132 
#define  USB_DESC_TYPE_DEVICE 131 
#define  USB_DESC_TYPE_DEVICE_QUALIFIER 130 
#define  USB_DESC_TYPE_OTHER_SPEED_CONFIGURATION 129 
#define  USB_DESC_TYPE_STRING 128 
 int* stub1 (TYPE_4__*,scalar_t__*) ; 
 scalar_t__ stub2 (TYPE_4__*,scalar_t__*) ; 
 scalar_t__ stub3 (TYPE_4__*,scalar_t__*) ; 
 int* stub4 (TYPE_4__*,int,scalar_t__*) ; 
 scalar_t__ stub5 (TYPE_4__*,scalar_t__*) ; 
 scalar_t__ stub6 (TYPE_4__*,scalar_t__*) ; 

__attribute__((used)) static void USBD_GetDescriptor(USBD_HandleTypeDef *pdev ,
                               USBD_SetupReqTypedef *req)
{
  uint16_t len;
  uint8_t *pbuf;


  switch (req->wValue >> 8)
  {
  case USB_DESC_TYPE_DEVICE:
    pbuf = pdev->pDesc->GetDeviceDescriptor(pdev, &len);
    break;

  case USB_DESC_TYPE_CONFIGURATION:
    if(pdev->dev_speed == USBD_SPEED_HIGH )
    {
      pbuf   = (uint8_t *)pdev->pClass->GetHSConfigDescriptor(pdev, &len);
      pbuf[1] = USB_DESC_TYPE_CONFIGURATION;
    }
    else
    {
      pbuf   = (uint8_t *)pdev->pClass->GetFSConfigDescriptor(pdev, &len);
      pbuf[1] = USB_DESC_TYPE_CONFIGURATION;
    }
    break;

  case USB_DESC_TYPE_STRING:
    pbuf = pdev->pDesc->GetStrDescriptor(pdev, req->wValue & 0xff, &len);
    if (pbuf == NULL) {
      USBD_CtlError(pdev, req);
      return;
    }
    break;

  case USB_DESC_TYPE_DEVICE_QUALIFIER:

    if(pdev->dev_speed == USBD_SPEED_HIGH  )
    {
      pbuf   = (uint8_t *)pdev->pClass->GetDeviceQualifierDescriptor(pdev, &len);
      break;
    }
    else
    {
      USBD_CtlError(pdev , req);
      return;
    }

  case USB_DESC_TYPE_OTHER_SPEED_CONFIGURATION:
    if(pdev->dev_speed == USBD_SPEED_HIGH  )
    {
      pbuf   = (uint8_t *)pdev->pClass->GetOtherSpeedConfigDescriptor(pdev, &len);
      pbuf[1] = USB_DESC_TYPE_OTHER_SPEED_CONFIGURATION;
      break;
    }
    else
    {
      USBD_CtlError(pdev , req);
      return;
    }

  default:
     USBD_CtlError(pdev , req);
    return;
  }

  if((len != 0)&& (req->wLength != 0))
  {

    len = MIN(len , req->wLength);

    USBD_CtlSendData (pdev,
                      pbuf,
                      len);
  }

}