#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_9__ {TYPE_1__* pActiveClass; } ;
typedef  TYPE_2__ USBH_HandleTypeDef ;
struct TYPE_10__ {scalar_t__ InPipe; scalar_t__ OutPipe; } ;
struct TYPE_8__ {TYPE_3__* pData; } ;
typedef  TYPE_3__ MSC_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USBH_ClosePipe (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  USBH_FreePipe (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  USBH_OK ; 
 int /*<<< orphan*/  USBH_free (TYPE_3__*) ; 

USBH_StatusTypeDef USBH_MSC_InterfaceDeInit (USBH_HandleTypeDef *phost)
{
  MSC_HandleTypeDef *MSC_Handle =  phost->pActiveClass->pData;

  if ( MSC_Handle->OutPipe)
  {
    USBH_ClosePipe(phost, MSC_Handle->OutPipe);
    USBH_FreePipe  (phost, MSC_Handle->OutPipe);
    MSC_Handle->OutPipe = 0;     /* Reset the Channel as Free */
  }
  
  if ( MSC_Handle->InPipe)
  {
    USBH_ClosePipe(phost, MSC_Handle->InPipe);
    USBH_FreePipe  (phost, MSC_Handle->InPipe);
    MSC_Handle->InPipe = 0;     /* Reset the Channel as Free */
  } 

  if(phost->pActiveClass->pData)
  {
    USBH_free (phost->pActiveClass->pData);
    phost->pActiveClass->pData = 0;
  }
  
  return USBH_OK;
}