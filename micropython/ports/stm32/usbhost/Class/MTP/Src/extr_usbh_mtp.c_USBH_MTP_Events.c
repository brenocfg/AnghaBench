#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_11__ {int Timer; TYPE_1__* pActiveClass; } ;
typedef  TYPE_3__ USBH_HandleTypeDef ;
struct TYPE_10__ {int state; int timer; int poll; int /*<<< orphan*/  container; } ;
struct TYPE_12__ {int /*<<< orphan*/  NotificationPipe; int /*<<< orphan*/  NotificationEpSize; TYPE_2__ events; } ;
struct TYPE_9__ {TYPE_4__* pData; } ;
typedef  TYPE_4__ MTP_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  MTP_DecodeEvent (TYPE_3__*) ; 
#define  MTP_EVENTS_GETDATA 129 
#define  MTP_EVENTS_INIT 128 
 int /*<<< orphan*/  USBH_BUSY ; 
 int /*<<< orphan*/  USBH_InterruptReceiveData (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_LL_GetURBState (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_URB_DONE ; 

__attribute__((used)) static USBH_StatusTypeDef USBH_MTP_Events (USBH_HandleTypeDef *phost)
{
  USBH_StatusTypeDef status = USBH_BUSY ;
  MTP_HandleTypeDef *MTP_Handle =  phost->pActiveClass->pData; 
 
  
  switch(MTP_Handle->events.state)
  {
  case MTP_EVENTS_INIT:
    if((phost->Timer & 1) == 0)
    {
      MTP_Handle->events.timer = phost->Timer;
      USBH_InterruptReceiveData(phost, 
                                (uint8_t *)&(MTP_Handle->events.container),
                                MTP_Handle->NotificationEpSize,
                                MTP_Handle->NotificationPipe);
      
      
     MTP_Handle->events.state = MTP_EVENTS_GETDATA ;
    }
    break;
  case MTP_EVENTS_GETDATA:
    if(USBH_LL_GetURBState(phost , MTP_Handle->NotificationPipe) == USBH_URB_DONE)
    {
      MTP_DecodeEvent(phost);
    }
    
    if(( phost->Timer - MTP_Handle->events.timer) >= MTP_Handle->events.poll)
    {
     MTP_Handle->events.timer = phost->Timer;
      
      USBH_InterruptReceiveData(phost, 
                                (uint8_t *)&(MTP_Handle->events.container),
                                MTP_Handle->NotificationEpSize,
                                MTP_Handle->NotificationPipe);     
      
    }
    break;

  default:  
    break; 
  }
    
  return status;  
}