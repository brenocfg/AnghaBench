#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_5__ {scalar_t__ speed; } ;
struct TYPE_6__ {TYPE_1__ device; } ;
typedef  TYPE_2__ USBH_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USBH_EP_CONTROL ; 
 int /*<<< orphan*/  USBH_LL_SubmitURB (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  USBH_OK ; 
 int /*<<< orphan*/  USBH_PID_DATA ; 
 scalar_t__ USBH_SPEED_HIGH ; 

USBH_StatusTypeDef USBH_CtlSendData (USBH_HandleTypeDef *phost, 
                                uint8_t *buff, 
                                uint16_t length,
                                uint8_t pipe_num,
                                uint8_t do_ping )
{
  if(phost->device.speed != USBH_SPEED_HIGH)
  {
    do_ping = 0;
  }
  
  USBH_LL_SubmitURB (phost,         /* Driver handle    */
                          pipe_num,             /* Pipe index       */
                          0,                    /* Direction : OUT  */
                          USBH_EP_CONTROL,      /* EP type          */                          
                          USBH_PID_DATA,        /* Type Data        */
                          buff,                 /* data buffer      */
                          length,               /* data length      */ 
                          do_ping);             /* do ping (HS Only)*/
  
  return USBH_OK;
}