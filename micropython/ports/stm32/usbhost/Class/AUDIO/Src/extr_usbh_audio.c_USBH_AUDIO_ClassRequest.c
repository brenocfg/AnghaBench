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
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_13__ {int /*<<< orphan*/  os_event; int /*<<< orphan*/  (* pUser ) (TYPE_4__*,int /*<<< orphan*/ ) ;TYPE_1__* pActiveClass; } ;
typedef  TYPE_4__ USBH_HandleTypeDef ;
struct TYPE_12__ {int supported; int /*<<< orphan*/  AltSettings; int /*<<< orphan*/  interface; int /*<<< orphan*/  asociated_channels; int /*<<< orphan*/  asociated_feature; } ;
struct TYPE_11__ {int supported; int /*<<< orphan*/  AltSettings; int /*<<< orphan*/  interface; } ;
struct TYPE_14__ {int req_state; int /*<<< orphan*/  play_state; TYPE_3__ headphone; TYPE_2__ microphone; void* cs_req_state; int /*<<< orphan*/  temp_channels; int /*<<< orphan*/  temp_feature; } ;
struct TYPE_10__ {TYPE_5__* pData; } ;
typedef  TYPE_5__ AUDIO_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_PLAYBACK_INIT ; 
#define  AUDIO_REQ_CS_REQUESTS 134 
 void* AUDIO_REQ_GET_VOLUME ; 
#define  AUDIO_REQ_IDLE 133 
#define  AUDIO_REQ_INIT 132 
#define  AUDIO_REQ_SET_DEFAULT_IN_INTERFACE 131 
#define  AUDIO_REQ_SET_DEFAULT_OUT_INTERFACE 130 
#define  AUDIO_REQ_SET_IN_INTERFACE 129 
#define  AUDIO_REQ_SET_OUT_INTERFACE 128 
 int /*<<< orphan*/  HOST_USER_CLASS_ACTIVE ; 
 int /*<<< orphan*/  USBH_AUDIO_HandleCSRequest (TYPE_4__*) ; 
 int /*<<< orphan*/  USBH_BUSY ; 
 int /*<<< orphan*/  USBH_CLASS_EVENT ; 
 int /*<<< orphan*/  USBH_OK ; 
 int /*<<< orphan*/  USBH_SetInterface (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_URB_EVENT ; 
 int /*<<< orphan*/  osMessagePut (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static USBH_StatusTypeDef USBH_AUDIO_ClassRequest(USBH_HandleTypeDef *phost)
{   
  AUDIO_HandleTypeDef *AUDIO_Handle =  phost->pActiveClass->pData;  
  USBH_StatusTypeDef status = USBH_BUSY;
  USBH_StatusTypeDef req_status = USBH_BUSY;
  
  /* Switch AUDIO REQ state machine */
  switch (AUDIO_Handle->req_state)
  {
  case AUDIO_REQ_INIT:
  case AUDIO_REQ_SET_DEFAULT_IN_INTERFACE:
    if(AUDIO_Handle->microphone.supported == 1)
    {
      req_status = USBH_SetInterface(phost, 
                                     AUDIO_Handle->microphone.interface, 
                                     0);
      
      if(req_status == USBH_OK)
      {
        AUDIO_Handle->req_state = AUDIO_REQ_SET_DEFAULT_OUT_INTERFACE;
      }
      
    }
    else
    {
      AUDIO_Handle->req_state = AUDIO_REQ_SET_DEFAULT_OUT_INTERFACE;
#if (USBH_USE_OS == 1)
      osMessagePut ( phost->os_event, USBH_URB_EVENT, 0);
#endif       
    }
    break;
    
  case AUDIO_REQ_SET_DEFAULT_OUT_INTERFACE:
    if(AUDIO_Handle->headphone.supported == 1)
    {
      req_status = USBH_SetInterface(phost, 
                                     AUDIO_Handle->headphone.interface, 
                                     0);
      
      if(req_status == USBH_OK)
      {
        AUDIO_Handle->req_state = AUDIO_REQ_CS_REQUESTS;
        AUDIO_Handle->cs_req_state = AUDIO_REQ_GET_VOLUME;
        
        AUDIO_Handle->temp_feature  = AUDIO_Handle->headphone.asociated_feature;
        AUDIO_Handle->temp_channels = AUDIO_Handle->headphone.asociated_channels;
      }
    }
    else
    {
        AUDIO_Handle->req_state = AUDIO_REQ_CS_REQUESTS;
        AUDIO_Handle->cs_req_state = AUDIO_REQ_GET_VOLUME;
#if (USBH_USE_OS == 1)
      osMessagePut ( phost->os_event, USBH_URB_EVENT, 0);
#endif         
    }
    break;
    
  case AUDIO_REQ_CS_REQUESTS:
    if(USBH_AUDIO_HandleCSRequest (phost) == USBH_OK)
    {
      AUDIO_Handle->req_state = AUDIO_REQ_SET_IN_INTERFACE;
    }
    break;
   
  case AUDIO_REQ_SET_IN_INTERFACE:
    if(AUDIO_Handle->microphone.supported == 1)
    {
      req_status = USBH_SetInterface(phost, 
                                     AUDIO_Handle->microphone.interface, 
                                     AUDIO_Handle->microphone.AltSettings);
      
      if(req_status == USBH_OK)
      {
        AUDIO_Handle->req_state = AUDIO_REQ_SET_OUT_INTERFACE;
      }
    }
    else
    {
      AUDIO_Handle->req_state = AUDIO_REQ_SET_OUT_INTERFACE;
#if (USBH_USE_OS == 1)
      osMessagePut ( phost->os_event, USBH_URB_EVENT, 0);
#endif       
    }
    break;
  case AUDIO_REQ_SET_OUT_INTERFACE:
   if(AUDIO_Handle->headphone.supported == 1)
    {
      req_status = USBH_SetInterface(phost, 
                                     AUDIO_Handle->headphone.interface, 
                                     AUDIO_Handle->headphone.AltSettings);
      
      if(req_status == USBH_OK)
      {
        AUDIO_Handle->req_state = AUDIO_REQ_IDLE;
      }
      
    }
   else
   {
     AUDIO_Handle->req_state = AUDIO_REQ_IDLE;
#if (USBH_USE_OS == 1)
      osMessagePut ( phost->os_event, USBH_URB_EVENT, 0);
#endif      
   }
   break;
  case AUDIO_REQ_IDLE:
    AUDIO_Handle->play_state = AUDIO_PLAYBACK_INIT;
    phost->pUser(phost, HOST_USER_CLASS_ACTIVE); 
    status  = USBH_OK;    
#if (USBH_USE_OS == 1)
      osMessagePut ( phost->os_event, USBH_CLASS_EVENT, 0);
#endif
  default:
    break;
  }
  return status; 
}