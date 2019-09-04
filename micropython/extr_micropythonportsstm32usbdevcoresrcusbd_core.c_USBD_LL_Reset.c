#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USBD_StatusTypeDef ;
struct TYPE_11__ {int /*<<< orphan*/  dev_config; TYPE_1__* pClass; scalar_t__ pClassData; int /*<<< orphan*/  dev_state; TYPE_3__* ep_in; TYPE_2__* ep_out; } ;
typedef  TYPE_4__ USBD_HandleTypeDef ;
struct TYPE_10__ {void* maxpacket; } ;
struct TYPE_9__ {void* maxpacket; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* DeInit ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_EP_TYPE_CTRL ; 
 int /*<<< orphan*/  USBD_LL_OpenEP (TYPE_4__*,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  USBD_OK ; 
 int /*<<< orphan*/  USBD_STATE_DEFAULT ; 
 void* USB_MAX_EP0_SIZE ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 

USBD_StatusTypeDef USBD_LL_Reset(USBD_HandleTypeDef  *pdev)
{
  /* Open EP0 OUT */
  USBD_LL_OpenEP(pdev,
              0x00,
              USBD_EP_TYPE_CTRL,
              USB_MAX_EP0_SIZE);

  pdev->ep_out[0].maxpacket = USB_MAX_EP0_SIZE;

  /* Open EP0 IN */
  USBD_LL_OpenEP(pdev,
              0x80,
              USBD_EP_TYPE_CTRL,
              USB_MAX_EP0_SIZE);

  pdev->ep_in[0].maxpacket = USB_MAX_EP0_SIZE;
  /* Upon Reset call usr call back */
  pdev->dev_state = USBD_STATE_DEFAULT;

  if (pdev->pClassData)
    pdev->pClass->DeInit(pdev, pdev->dev_config);


  return USBD_OK;
}