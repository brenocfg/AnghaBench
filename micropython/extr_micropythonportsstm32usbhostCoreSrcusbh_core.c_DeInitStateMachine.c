#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_6__ {int /*<<< orphan*/  speed; int /*<<< orphan*/  address; scalar_t__* Data; } ;
struct TYPE_5__ {scalar_t__ errorcount; int /*<<< orphan*/  pipe_size; int /*<<< orphan*/  state; } ;
struct TYPE_7__ {TYPE_2__ device; TYPE_1__ Control; scalar_t__ Timer; int /*<<< orphan*/  RequestState; int /*<<< orphan*/  EnumState; int /*<<< orphan*/  gState; scalar_t__* Pipes; } ;
typedef  TYPE_3__ USBH_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SEND ; 
 int /*<<< orphan*/  CTRL_SETUP ; 
 int /*<<< orphan*/  ENUM_IDLE ; 
 int /*<<< orphan*/  HOST_IDLE ; 
 int /*<<< orphan*/  USBH_ADDRESS_DEFAULT ; 
 size_t USBH_MAX_DATA_BUFFER ; 
 size_t USBH_MAX_PIPES_NBR ; 
 int /*<<< orphan*/  USBH_MPS_DEFAULT ; 
 int /*<<< orphan*/  USBH_OK ; 
 int /*<<< orphan*/  USBH_SPEED_FULL ; 

__attribute__((used)) static USBH_StatusTypeDef  DeInitStateMachine(USBH_HandleTypeDef *phost)
{
  uint32_t i = 0;

  /* Clear Pipes flags*/
  for ( ; i < USBH_MAX_PIPES_NBR; i++)
  {
    phost->Pipes[i] = 0;
  }
  
  for(i = 0; i< USBH_MAX_DATA_BUFFER; i++)
  {
    phost->device.Data[i] = 0;
  }
  
  phost->gState = HOST_IDLE;
  phost->EnumState = ENUM_IDLE;
  phost->RequestState = CMD_SEND;
  phost->Timer = 0;  
  
  phost->Control.state = CTRL_SETUP;
  phost->Control.pipe_size = USBH_MPS_DEFAULT;  
  phost->Control.errorcount = 0;
  
  phost->device.address = USBH_ADDRESS_DEFAULT;
  phost->device.speed   = USBH_SPEED_FULL;
  
  return USBH_OK;
}