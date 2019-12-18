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
typedef  int uint8_t ;
typedef  scalar_t__ USBH_StatusTypeDef ;
struct TYPE_11__ {TYPE_1__* pActiveClass; } ;
typedef  TYPE_4__ USBH_HandleTypeDef ;
struct TYPE_9__ {scalar_t__ volume; scalar_t__ volumeMax; scalar_t__ volumeMin; int /*<<< orphan*/  resolution; } ;
struct TYPE_10__ {int asociated_channels; int /*<<< orphan*/  asociated_feature; TYPE_2__ attribute; } ;
struct TYPE_12__ {int temp_channels; int /*<<< orphan*/  cs_req_state; TYPE_3__ headphone; int /*<<< orphan*/  temp_feature; } ;
struct TYPE_8__ {TYPE_5__* pData; } ;
typedef  TYPE_5__ AUDIO_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_REQ_GET_VOLUME ; 
 scalar_t__ AUDIO_SetVolume (TYPE_4__*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 scalar_t__ USBH_BUSY ; 
 scalar_t__ USBH_OK ; 

__attribute__((used)) static USBH_StatusTypeDef USBH_AUDIO_SetControlAttribute (USBH_HandleTypeDef *phost, uint8_t attrib)
{
  USBH_StatusTypeDef status = USBH_BUSY ;
  AUDIO_HandleTypeDef *AUDIO_Handle; 

  
  AUDIO_Handle = phost->pActiveClass->pData;
  
  switch (attrib)
  {
  case 0x01:
    AUDIO_Handle->headphone.attribute.volume += AUDIO_Handle->headphone.attribute.resolution;
    break;
    
  case 0x02:
    AUDIO_Handle->headphone.attribute.volume -= AUDIO_Handle->headphone.attribute.resolution; 
    break;
    
  }
  
  if(AUDIO_Handle->headphone.attribute.volume > AUDIO_Handle->headphone.attribute.volumeMax)
  {
    AUDIO_Handle->headphone.attribute.volume =AUDIO_Handle->headphone.attribute.volumeMax;
  }
  
  if(AUDIO_Handle->headphone.attribute.volume < AUDIO_Handle->headphone.attribute.volumeMin)
  {
    AUDIO_Handle->headphone.attribute.volume =AUDIO_Handle->headphone.attribute.volumeMin;
  }
  
  if(AUDIO_SetVolume (phost, 
                                 AUDIO_Handle->temp_feature, 
                                 AUDIO_Handle->temp_channels, 
                                 AUDIO_Handle->headphone.attribute.volume) != USBH_BUSY)
  {
    
    if(AUDIO_Handle->temp_channels ==  1)
    {
      AUDIO_Handle->temp_feature  = AUDIO_Handle->headphone.asociated_feature;
      AUDIO_Handle->temp_channels = AUDIO_Handle->headphone.asociated_channels;
      status = USBH_OK;
    }
    else
    {
      AUDIO_Handle->temp_channels--;
    }
    AUDIO_Handle->cs_req_state = AUDIO_REQ_GET_VOLUME;
  }
  
 
  return status;
}