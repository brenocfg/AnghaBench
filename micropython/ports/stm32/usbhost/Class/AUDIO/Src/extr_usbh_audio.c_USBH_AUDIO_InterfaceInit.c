#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ USBH_StatusTypeDef ;
struct TYPE_26__ {int /*<<< orphan*/  speed; int /*<<< orphan*/  address; } ;
struct TYPE_29__ {TYPE_5__ device; TYPE_1__* pActiveClass; } ;
typedef  TYPE_8__ USBH_HandleTypeDef ;
struct TYPE_25__ {int supported; scalar_t__ EpSize; void* Pipe; int /*<<< orphan*/  Ep; } ;
struct TYPE_28__ {scalar_t__ EpSize; int supported; void* Pipe; int /*<<< orphan*/  Ep; int /*<<< orphan*/  Poll; int /*<<< orphan*/  AltSettings; int /*<<< orphan*/  interface; } ;
struct TYPE_27__ {scalar_t__ EpSize; int supported; void* Pipe; int /*<<< orphan*/  Ep; int /*<<< orphan*/  Poll; int /*<<< orphan*/  AltSettings; int /*<<< orphan*/  interface; } ;
struct TYPE_30__ {int /*<<< orphan*/  control_state; int /*<<< orphan*/  req_state; TYPE_4__ control; TYPE_7__ microphone; TYPE_6__ headphone; TYPE_3__* stream_out; TYPE_2__* stream_in; } ;
struct TYPE_24__ {int valid; scalar_t__ EpSize; int /*<<< orphan*/  Poll; int /*<<< orphan*/  Ep; int /*<<< orphan*/  AltSettings; int /*<<< orphan*/  interface; } ;
struct TYPE_23__ {int valid; scalar_t__ EpSize; int /*<<< orphan*/  Ep; int /*<<< orphan*/  AltSettings; int /*<<< orphan*/  interface; } ;
struct TYPE_22__ {int /*<<< orphan*/  Name; TYPE_9__* pData; } ;
typedef  TYPE_9__ AUDIO_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  AC_CLASS ; 
 int /*<<< orphan*/  AUDIO_CONTROL_INIT ; 
 int AUDIO_MAX_AUDIO_STD_INTERFACE ; 
 int /*<<< orphan*/  AUDIO_REQ_INIT ; 
 int /*<<< orphan*/  USBH_AUDIO_BuildHeadphonePath (TYPE_8__*) ; 
 int /*<<< orphan*/  USBH_AUDIO_BuildMicrophonePath (TYPE_8__*) ; 
 scalar_t__ USBH_AUDIO_FindAudioStreamingIN (TYPE_8__*) ; 
 scalar_t__ USBH_AUDIO_FindAudioStreamingOUT (TYPE_8__*) ; 
 scalar_t__ USBH_AUDIO_FindHIDControl (TYPE_8__*) ; 
 int /*<<< orphan*/  USBH_AUDIO_ParseCSDescriptors (TYPE_8__*) ; 
 void* USBH_AllocPipe (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_DbgLog (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ USBH_FAIL ; 
 int USBH_FindInterface (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USBH_LL_SetToggle (TYPE_8__*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ USBH_OK ; 
 int /*<<< orphan*/  USBH_OpenPipe (TYPE_8__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ USBH_malloc (int) ; 
 int /*<<< orphan*/  USBH_memset (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USB_EP_TYPE_INTR ; 
 int /*<<< orphan*/  USB_EP_TYPE_ISOC ; 
 int /*<<< orphan*/  USB_SUBCLASS_AUDIOCONTROL ; 

__attribute__((used)) static USBH_StatusTypeDef USBH_AUDIO_InterfaceInit (USBH_HandleTypeDef *phost)
{
  USBH_StatusTypeDef status = USBH_FAIL ;
  USBH_StatusTypeDef out_status, in_status ;    
  AUDIO_HandleTypeDef *AUDIO_Handle;
  uint8_t  interface, index;
  uint16_t ep_size_out = 0;
  uint16_t ep_size_in = 0;  
  
  interface = USBH_FindInterface(phost, AC_CLASS, USB_SUBCLASS_AUDIOCONTROL, 0x00);
  
  if(interface == 0xFF) /* Not Valid Interface */
  {
    USBH_DbgLog ("Cannot Find the interface for %s class.", phost->pActiveClass->Name);
    status = USBH_FAIL;      
  }
  else
  {
    
    
    phost->pActiveClass->pData = (AUDIO_HandleTypeDef *)USBH_malloc (sizeof(AUDIO_HandleTypeDef));
    AUDIO_Handle =  phost->pActiveClass->pData; 
    USBH_memset(AUDIO_Handle, 0, sizeof(AUDIO_HandleTypeDef));
    
    
    /* 1st Step:  Find Audio Interfaces */
    out_status = USBH_AUDIO_FindAudioStreamingIN (phost);
    
    in_status = USBH_AUDIO_FindAudioStreamingOUT(phost);
    
    if((out_status == USBH_FAIL) && (in_status == USBH_FAIL))
    {
      USBH_DbgLog ("%s class configuration not supported.", phost->pActiveClass->Name);
    }
    else
    {
      /* 2nd Step:  Select Audio Streaming Interfaces with largest endpoint size : default behavior*/ 
      for (index = 0; index < AUDIO_MAX_AUDIO_STD_INTERFACE; index ++)
      {
        if( AUDIO_Handle->stream_out[index].valid == 1)
        {
          if(ep_size_out < AUDIO_Handle->stream_out[index].EpSize)
          {
            ep_size_out = AUDIO_Handle->stream_out[index].EpSize;
            AUDIO_Handle->headphone.interface = AUDIO_Handle->stream_out[index].interface;
            AUDIO_Handle->headphone.AltSettings = AUDIO_Handle->stream_out[index].AltSettings;           
            AUDIO_Handle->headphone.Ep = AUDIO_Handle->stream_out[index].Ep;
            AUDIO_Handle->headphone.EpSize = AUDIO_Handle->stream_out[index].EpSize; 
            AUDIO_Handle->headphone.Poll = AUDIO_Handle->stream_out[index].Poll;
            AUDIO_Handle->headphone.supported = 1;  
          }
        }
        
        if( AUDIO_Handle->stream_in[index].valid == 1)
        {
          if(ep_size_in < AUDIO_Handle->stream_in[index].EpSize)
          {
            ep_size_in = AUDIO_Handle->stream_in[index].EpSize;
            AUDIO_Handle->microphone.interface = AUDIO_Handle->stream_in[index].interface;
            AUDIO_Handle->microphone.AltSettings = AUDIO_Handle->stream_in[index].AltSettings;                
            AUDIO_Handle->microphone.Ep = AUDIO_Handle->stream_in[index].Ep;
            AUDIO_Handle->microphone.EpSize = AUDIO_Handle->stream_in[index].EpSize;
            AUDIO_Handle->microphone.Poll = AUDIO_Handle->stream_out[index].Poll;         
            AUDIO_Handle->microphone.supported = 1;       
          }
        }
      }
      
      if(USBH_AUDIO_FindHIDControl(phost) == USBH_OK)
      {
        AUDIO_Handle->control.supported = 1;
      }
      
      /* 3rd Step:  Find and Parse Audio interfaces */ 
      USBH_AUDIO_ParseCSDescriptors (phost);
     
      
      /* 4th Step:  Open the Audio streaming pipes*/ 
      if(AUDIO_Handle->headphone.supported == 1)
      {
        USBH_AUDIO_BuildHeadphonePath (phost);
         
        AUDIO_Handle->headphone.Pipe  = USBH_AllocPipe(phost, AUDIO_Handle->headphone.Ep);
        
        /* Open pipe for IN endpoint */
        USBH_OpenPipe  (phost,
                        AUDIO_Handle->headphone.Pipe,
                        AUDIO_Handle->headphone.Ep,
                        phost->device.address,
                        phost->device.speed,
                        USB_EP_TYPE_ISOC,
                        AUDIO_Handle->headphone.EpSize); 
        
        USBH_LL_SetToggle (phost,  AUDIO_Handle->headphone.Pipe, 0);          
        
      }
      
      if(AUDIO_Handle->microphone.supported == 1)
      {
        USBH_AUDIO_BuildMicrophonePath (phost);        
        AUDIO_Handle->microphone.Pipe  = USBH_AllocPipe(phost, AUDIO_Handle->microphone.Ep);
        
        /* Open pipe for IN endpoint */
        USBH_OpenPipe  (phost,
                        AUDIO_Handle->microphone.Pipe,
                        AUDIO_Handle->microphone.Ep,
                        phost->device.address,
                        phost->device.speed,
                        USB_EP_TYPE_ISOC,
                        AUDIO_Handle->microphone.EpSize); 
        
        USBH_LL_SetToggle (phost,  AUDIO_Handle->microphone.Pipe, 0);  
      }
      
      if(AUDIO_Handle->control.supported == 1)
      {     
        AUDIO_Handle->control.Pipe  = USBH_AllocPipe(phost, AUDIO_Handle->control.Ep);
        
        /* Open pipe for IN endpoint */
        USBH_OpenPipe  (phost,
                        AUDIO_Handle->control.Pipe,
                        AUDIO_Handle->control.Ep,
                        phost->device.address,
                        phost->device.speed,
                        USB_EP_TYPE_INTR,
                        AUDIO_Handle->control.EpSize); 
        
        USBH_LL_SetToggle (phost,  AUDIO_Handle->control.Pipe, 0);          
   
      }
      
      AUDIO_Handle->req_state     = AUDIO_REQ_INIT;
      AUDIO_Handle->control_state = AUDIO_CONTROL_INIT;
      
      status = USBH_OK;
    }
  }
  return status;
}