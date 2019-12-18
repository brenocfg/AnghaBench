#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_11__ {scalar_t__ gState; TYPE_1__* pActiveClass; } ;
typedef  TYPE_4__ USBH_HandleTypeDef ;
struct TYPE_10__ {int /*<<< orphan*/  OutPipe; int /*<<< orphan*/  InPipe; } ;
struct TYPE_9__ {int /*<<< orphan*/  NotifPipe; } ;
struct TYPE_12__ {TYPE_3__ DataItf; TYPE_2__ CommItf; int /*<<< orphan*/  state; } ;
struct TYPE_8__ {TYPE_5__* pData; } ;
typedef  TYPE_5__ CDC_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  CDC_IDLE_STATE ; 
 scalar_t__ HOST_CLASS ; 
 int /*<<< orphan*/  USBH_ClosePipe (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_OK ; 

USBH_StatusTypeDef  USBH_CDC_Stop(USBH_HandleTypeDef *phost)
{
  CDC_HandleTypeDef *CDC_Handle =  phost->pActiveClass->pData; 
  
  if(phost->gState == HOST_CLASS)
  {
    CDC_Handle->state = CDC_IDLE_STATE;
    
    USBH_ClosePipe(phost, CDC_Handle->CommItf.NotifPipe);
    USBH_ClosePipe(phost, CDC_Handle->DataItf.InPipe);
    USBH_ClosePipe(phost, CDC_Handle->DataItf.OutPipe);
  }
  return USBH_OK;  
}