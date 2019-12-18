#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_17__ {int /*<<< orphan*/  os_event; TYPE_1__* pActiveClass; } ;
typedef  TYPE_6__ USBH_HandleTypeDef ;
struct TYPE_16__ {size_t asociated_as; int /*<<< orphan*/  Ep; int /*<<< orphan*/  frequency; } ;
struct TYPE_15__ {TYPE_3__* as_desc; } ;
struct TYPE_18__ {int play_state; TYPE_5__ headphone; TYPE_4__ class_desc; } ;
struct TYPE_14__ {TYPE_2__* FormatTypeDesc; } ;
struct TYPE_13__ {scalar_t__* tSamFreq; int /*<<< orphan*/  bSamFreqType; } ;
struct TYPE_12__ {TYPE_7__* pData; } ;
typedef  TYPE_7__ AUDIO_HandleTypeDef ;

/* Variables and functions */
#define  AUDIO_PLAYBACK_IDLE 132 
#define  AUDIO_PLAYBACK_INIT 131 
#define  AUDIO_PLAYBACK_PLAY 130 
#define  AUDIO_PLAYBACK_SET_EP 129 
#define  AUDIO_PLAYBACK_SET_EP_FREQ 128 
 int /*<<< orphan*/  USBH_AUDIO_FrequencySet (TYPE_6__*) ; 
 int /*<<< orphan*/  USBH_AUDIO_SetEndpointControls (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USBH_AUDIO_Transmit (TYPE_6__*) ; 
 int /*<<< orphan*/  USBH_BUSY ; 
 int /*<<< orphan*/  USBH_CLASS_EVENT ; 
 int /*<<< orphan*/  USBH_OK ; 
 int /*<<< orphan*/  USBH_URB_EVENT ; 
 int /*<<< orphan*/  osMessagePut (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static USBH_StatusTypeDef USBH_AUDIO_OutputStream (USBH_HandleTypeDef *phost)
{
  USBH_StatusTypeDef status = USBH_BUSY ;
  AUDIO_HandleTypeDef *AUDIO_Handle =  phost->pActiveClass->pData;   
  uint8_t *buff;
  
  
  switch(AUDIO_Handle->play_state)
  {
  case AUDIO_PLAYBACK_INIT:
    
    if( AUDIO_Handle->class_desc.as_desc[AUDIO_Handle->headphone.asociated_as].FormatTypeDesc->bSamFreqType == 0)
    {
      AUDIO_Handle->play_state = AUDIO_PLAYBACK_SET_EP_FREQ;        
    }
    else
    {
      AUDIO_Handle->play_state = AUDIO_PLAYBACK_SET_EP;
    }
#if (USBH_USE_OS == 1)
      osMessagePut ( phost->os_event, USBH_URB_EVENT, 0);
#endif  
    break;
    
  case AUDIO_PLAYBACK_SET_EP_FREQ:

    buff = (uint8_t*)AUDIO_Handle->class_desc.as_desc[AUDIO_Handle->headphone.asociated_as].FormatTypeDesc->tSamFreq[0];    

    status = USBH_AUDIO_SetEndpointControls(phost, AUDIO_Handle->headphone.Ep, buff);
    if(status == USBH_OK) 
    {
      AUDIO_Handle->play_state = AUDIO_PLAYBACK_IDLE;    
    }
    break;
    
  case AUDIO_PLAYBACK_SET_EP:
    buff = (uint8_t *)&AUDIO_Handle->headphone.frequency;    
    status = USBH_AUDIO_SetEndpointControls(phost,AUDIO_Handle->headphone.Ep, buff);
    if(status == USBH_OK)
    {
      AUDIO_Handle->play_state = AUDIO_PLAYBACK_IDLE;
      USBH_AUDIO_FrequencySet(phost);
    }
    break;
  case AUDIO_PLAYBACK_IDLE:
#if (USBH_USE_OS == 1)
      osMessagePut ( phost->os_event, USBH_CLASS_EVENT, 0);
#endif      
    status = USBH_OK;
    break;
    
  case AUDIO_PLAYBACK_PLAY:
    USBH_AUDIO_Transmit(phost);
    status = USBH_OK;
    break;
    
  default:
    break;
  }  
  
  return status;
}