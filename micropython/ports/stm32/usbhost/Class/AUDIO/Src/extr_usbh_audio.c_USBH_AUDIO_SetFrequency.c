#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_14__ {scalar_t__ gState; TYPE_1__* pActiveClass; } ;
typedef  TYPE_6__ USBH_HandleTypeDef ;
struct TYPE_13__ {size_t asociated_as; scalar_t__ frame_length; scalar_t__ frequency; } ;
struct TYPE_12__ {TYPE_3__* as_desc; } ;
struct TYPE_15__ {scalar_t__ play_state; TYPE_5__ headphone; TYPE_4__ class_desc; } ;
struct TYPE_11__ {TYPE_2__* FormatTypeDesc; } ;
struct TYPE_10__ {scalar_t__ bSamFreqType; int bLength; int /*<<< orphan*/ * tSamFreq; } ;
struct TYPE_9__ {TYPE_7__* pData; } ;
typedef  TYPE_7__ AUDIO_HandleTypeDef ;

/* Variables and functions */
 scalar_t__ AUDIO_PLAYBACK_IDLE ; 
 scalar_t__ AUDIO_PLAYBACK_SET_EP ; 
 size_t FALSE ; 
 scalar_t__ HOST_CLASS ; 
 scalar_t__ LE24 (int /*<<< orphan*/ ) ; 
 size_t TRUE ; 
 int /*<<< orphan*/  USBH_BUSY ; 
 int /*<<< orphan*/  USBH_OK ; 

USBH_StatusTypeDef USBH_AUDIO_SetFrequency (USBH_HandleTypeDef *phost, 
                                            uint16_t SampleRate,
                                            uint8_t  NbrChannels,
                                            uint8_t  BitPerSample)
{
  USBH_StatusTypeDef Status = USBH_BUSY;
  AUDIO_HandleTypeDef *AUDIO_Handle; 
  uint8_t              index; 
  uint8_t              change_freq = FALSE;
  uint32_t             freq_min, freq_max;
  uint8_t              num_supported_freq;
  
  if(phost->gState == HOST_CLASS)
  {
    AUDIO_Handle =  phost->pActiveClass->pData;
    if(AUDIO_Handle->play_state == AUDIO_PLAYBACK_IDLE)
    {
      
      if(AUDIO_Handle->class_desc.as_desc[AUDIO_Handle->headphone.asociated_as].FormatTypeDesc->bSamFreqType == 0)
      { 
        freq_min = LE24(AUDIO_Handle->class_desc.as_desc[AUDIO_Handle->headphone.asociated_as].FormatTypeDesc->tSamFreq[0]); 
        freq_max = LE24(AUDIO_Handle->class_desc.as_desc[AUDIO_Handle->headphone.asociated_as].FormatTypeDesc->tSamFreq[1]);         
        
        if(( SampleRate >= freq_min)&& (SampleRate <= freq_max))
        {
          change_freq = TRUE;
        }
      }
      else
      {    
        
        num_supported_freq = (AUDIO_Handle->class_desc.as_desc[AUDIO_Handle->headphone.asociated_as].FormatTypeDesc->bLength - 8)/3;
        
        
        for(index = 0; index < num_supported_freq; index++)
        {
          if(SampleRate == LE24(AUDIO_Handle->class_desc.as_desc[AUDIO_Handle->headphone.asociated_as].FormatTypeDesc->tSamFreq[index]))
          {
            change_freq = TRUE;            
            break;
          }
        }  
      }      
      
      if(change_freq == TRUE)
      {
        AUDIO_Handle->headphone.frequency = SampleRate;
        AUDIO_Handle->headphone.frame_length    = (SampleRate * BitPerSample * NbrChannels) / 8000;
        AUDIO_Handle->play_state = AUDIO_PLAYBACK_SET_EP;
        Status = USBH_OK;  
        
      }
    }
  }
   return Status;  
}