#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  USBD_StatusTypeDef ;
struct TYPE_10__ {scalar_t__ ep0_state; scalar_t__ dev_state; TYPE_1__* pClass; TYPE_3__* ep_out; } ;
typedef  TYPE_2__ USBD_HandleTypeDef ;
struct TYPE_11__ {scalar_t__ rem_length; scalar_t__ maxpacket; } ;
typedef  TYPE_3__ USBD_EndpointTypeDef ;
struct TYPE_9__ {int /*<<< orphan*/  (* DataOut ) (TYPE_2__*,scalar_t__) ;int /*<<< orphan*/  (* EP0_RxReady ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  USBD_CtlContinueRx (TYPE_2__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_CtlSendStatus (TYPE_2__*) ; 
 scalar_t__ USBD_EP0_DATA_OUT ; 
 int /*<<< orphan*/  USBD_OK ; 
 scalar_t__ USBD_STATE_CONFIGURED ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,scalar_t__) ; 

USBD_StatusTypeDef USBD_LL_DataOutStage(USBD_HandleTypeDef *pdev , uint8_t epnum, uint8_t *pdata)
{
  USBD_EndpointTypeDef    *pep;

  if(epnum == 0)
  {
    pep = &pdev->ep_out[0];

    if ( pdev->ep0_state == USBD_EP0_DATA_OUT)
    {
      if(pep->rem_length > pep->maxpacket)
      {
        pep->rem_length -=  pep->maxpacket;

        USBD_CtlContinueRx (pdev,
                            pdata,
                            MIN(pep->rem_length ,pep->maxpacket));
      }
      else
      {
        if((pdev->pClass->EP0_RxReady != NULL)&&
           (pdev->dev_state == USBD_STATE_CONFIGURED))
        {
          pdev->pClass->EP0_RxReady(pdev);
        }
        USBD_CtlSendStatus(pdev);
      }
    }
  }
  else if((pdev->pClass->DataOut != NULL)&&
          (pdev->dev_state == USBD_STATE_CONFIGURED))
  {
    pdev->pClass->DataOut(pdev, epnum);
  }
  return USBD_OK;
}