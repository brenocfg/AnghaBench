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
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_5__ {int is_connected; } ;
struct TYPE_6__ {scalar_t__ gState; int /*<<< orphan*/  os_event; int /*<<< orphan*/  (* pUser ) (TYPE_2__*,int /*<<< orphan*/ ) ;TYPE_1__ device; } ;
typedef  TYPE_2__ USBH_HandleTypeDef ;

/* Variables and functions */
 scalar_t__ HOST_DEV_ATTACHED ; 
 scalar_t__ HOST_DEV_WAIT_FOR_ATTACHMENT ; 
 scalar_t__ HOST_IDLE ; 
 int /*<<< orphan*/  HOST_USER_CONNECTION ; 
 int /*<<< orphan*/  USBH_OK ; 
 int /*<<< orphan*/  USBH_PORT_EVENT ; 
 int /*<<< orphan*/  osMessagePut (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

USBH_StatusTypeDef  USBH_LL_Connect  (USBH_HandleTypeDef *phost)
{
  if(phost->gState == HOST_IDLE )
  {
    phost->device.is_connected = 1;
    phost->gState = HOST_IDLE ;
    
    if(phost->pUser != NULL)
    {    
      phost->pUser(phost, HOST_USER_CONNECTION);
    }
  } 
  else if(phost->gState == HOST_DEV_WAIT_FOR_ATTACHMENT )
  {
    phost->gState = HOST_DEV_ATTACHED ;
  }
#if (USBH_USE_OS == 1)
  osMessagePut ( phost->os_event, USBH_PORT_EVENT, 0);
#endif 
  
  return USBH_OK;
}