#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_13__ {int Timer; TYPE_1__* pActiveClass; } ;
typedef  TYPE_4__ USBH_HandleTypeDef ;
struct TYPE_12__ {int timer; int Poll; int /*<<< orphan*/  Pipe; int /*<<< orphan*/  EpSize; } ;
struct TYPE_11__ {int /*<<< orphan*/  asociated_channels; int /*<<< orphan*/  asociated_feature; } ;
struct TYPE_14__ {int control_state; TYPE_3__ control; int /*<<< orphan*/ * mem; TYPE_2__ headphone; int /*<<< orphan*/  temp_channels; int /*<<< orphan*/  temp_feature; } ;
struct TYPE_10__ {TYPE_5__* pData; } ;
typedef  TYPE_5__ AUDIO_HandleTypeDef ;

/* Variables and functions */
#define  AUDIO_CONTROL_CHANGE 132 
#define  AUDIO_CONTROL_IDLE 131 
#define  AUDIO_CONTROL_INIT 130 
#define  AUDIO_CONTROL_VOLUME_DOWN 129 
#define  AUDIO_CONTROL_VOLUME_UP 128 
 int LE16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USBH_AUDIO_SetControlAttribute (TYPE_4__*,int) ; 
 int /*<<< orphan*/  USBH_BUSY ; 
 int /*<<< orphan*/  USBH_InterruptReceiveData (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_LL_GetURBState (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_OK ; 
 int /*<<< orphan*/  USBH_URB_DONE ; 

__attribute__((used)) static USBH_StatusTypeDef USBH_AUDIO_Control (USBH_HandleTypeDef *phost)
{
  USBH_StatusTypeDef status = USBH_BUSY ;
  AUDIO_HandleTypeDef *AUDIO_Handle =  phost->pActiveClass->pData; 
  uint16_t attribute  = 0; 
 
  
  switch(AUDIO_Handle->control_state)
  {
  case AUDIO_CONTROL_INIT:
    if((phost->Timer & 1) == 0)
    {
      AUDIO_Handle->control.timer = phost->Timer;
      USBH_InterruptReceiveData(phost, 
                                (uint8_t *)(AUDIO_Handle->mem),
                                AUDIO_Handle->control.EpSize,
                                AUDIO_Handle->control.Pipe);
      
      AUDIO_Handle->temp_feature  = AUDIO_Handle->headphone.asociated_feature;
      AUDIO_Handle->temp_channels = AUDIO_Handle->headphone.asociated_channels;
      
      AUDIO_Handle->control_state = AUDIO_CONTROL_CHANGE ;
    }
    break;
  case AUDIO_CONTROL_CHANGE:
    if(USBH_LL_GetURBState(phost , AUDIO_Handle->control.Pipe) == USBH_URB_DONE)
    {
      attribute = LE16(&AUDIO_Handle->mem[0]); 
      if(USBH_AUDIO_SetControlAttribute (phost, attribute) == USBH_BUSY)
      {
        break;
      }
    }
    
    if(( phost->Timer - AUDIO_Handle->control.timer) >= AUDIO_Handle->control.Poll)
    {
      AUDIO_Handle->control.timer = phost->Timer;
      
      USBH_InterruptReceiveData(phost, 
                                (uint8_t *)(AUDIO_Handle->mem),
                                AUDIO_Handle->control.EpSize,
                                AUDIO_Handle->control.Pipe);      
      
    }
    break;
    
  case AUDIO_CONTROL_VOLUME_UP:
       if( USBH_AUDIO_SetControlAttribute (phost, 1) == USBH_OK)
       {
         AUDIO_Handle->control_state = AUDIO_CONTROL_INIT;
        status = USBH_OK; 
       }
       break;
       
  case AUDIO_CONTROL_VOLUME_DOWN:
       if( USBH_AUDIO_SetControlAttribute (phost, 2) == USBH_OK)
       {
         AUDIO_Handle->control_state = AUDIO_CONTROL_INIT;         
         status = USBH_OK; 
       }     
       break;
       
  case AUDIO_CONTROL_IDLE:
  default:  
    break; 
  }
    
  return status;  
}