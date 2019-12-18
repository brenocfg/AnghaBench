#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  USBD_StatusTypeDef ;
struct TYPE_11__ {scalar_t__ ep0_state; int ep0_data_len; scalar_t__ dev_state; int dev_test_mode; TYPE_1__* pClass; TYPE_3__* ep_in; } ;
typedef  TYPE_2__ USBD_HandleTypeDef ;
struct TYPE_12__ {int rem_length; int maxpacket; int total_length; } ;
typedef  TYPE_3__ USBD_EndpointTypeDef ;
struct TYPE_10__ {int /*<<< orphan*/  (* DataIn ) (TYPE_2__*,scalar_t__) ;int /*<<< orphan*/  (* EP0_TxSent ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_CtlContinueSendData (TYPE_2__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  USBD_CtlReceiveStatus (TYPE_2__*) ; 
 scalar_t__ USBD_EP0_DATA_IN ; 
 int /*<<< orphan*/  USBD_OK ; 
 int /*<<< orphan*/  USBD_RunTestMode (TYPE_2__*) ; 
 scalar_t__ USBD_STATE_CONFIGURED ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,scalar_t__) ; 

USBD_StatusTypeDef USBD_LL_DataInStage(USBD_HandleTypeDef *pdev ,uint8_t epnum, uint8_t *pdata)
{
  USBD_EndpointTypeDef    *pep;

  if(epnum == 0)
  {
    pep = &pdev->ep_in[0];

    if ( pdev->ep0_state == USBD_EP0_DATA_IN)
    {
      if(pep->rem_length > pep->maxpacket)
      {
        pep->rem_length -=  pep->maxpacket;

        USBD_CtlContinueSendData (pdev,
                                  pdata,
                                  pep->rem_length);
      }
      else
      { /* last packet is MPS multiple, so send ZLP packet */
        if((pep->total_length % pep->maxpacket == 0) &&
           (pep->total_length >= pep->maxpacket) &&
             (pep->total_length < pdev->ep0_data_len ))
        {

          USBD_CtlContinueSendData(pdev , NULL, 0);
          pdev->ep0_data_len = 0;
        }
        else
        {
          if((pdev->pClass->EP0_TxSent != NULL)&&
             (pdev->dev_state == USBD_STATE_CONFIGURED))
          {
            pdev->pClass->EP0_TxSent(pdev);
          }
          USBD_CtlReceiveStatus(pdev);
        }
      }
    }
    if (pdev->dev_test_mode == 1)
    {
      USBD_RunTestMode(pdev);
      pdev->dev_test_mode = 0;
    }
  }
  else if((pdev->pClass->DataIn != NULL)&&
          (pdev->dev_state == USBD_STATE_CONFIGURED))
  {
    pdev->pClass->DataIn(pdev, epnum);
  }
  return USBD_OK;
}