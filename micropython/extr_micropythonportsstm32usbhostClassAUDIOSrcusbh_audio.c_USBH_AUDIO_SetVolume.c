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
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_6__ {scalar_t__ gState; TYPE_1__* pActiveClass; } ;
typedef  TYPE_2__ USBH_HandleTypeDef ;
struct TYPE_7__ {scalar_t__ play_state; int /*<<< orphan*/  control_state; } ;
struct TYPE_5__ {TYPE_3__* pData; } ;
typedef  scalar_t__ AUDIO_VolumeCtrlTypeDef ;
typedef  TYPE_3__ AUDIO_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_CONTROL_VOLUME_DOWN ; 
 int /*<<< orphan*/  AUDIO_CONTROL_VOLUME_UP ; 
 scalar_t__ AUDIO_PLAYBACK_PLAY ; 
 scalar_t__ HOST_CLASS ; 
 int /*<<< orphan*/  USBH_FAIL ; 
 int /*<<< orphan*/  USBH_OK ; 
 scalar_t__ VOLUME_DOWN ; 
 scalar_t__ VOLUME_UP ; 

USBH_StatusTypeDef USBH_AUDIO_SetVolume (USBH_HandleTypeDef *phost, AUDIO_VolumeCtrlTypeDef volume_ctl)
{
  AUDIO_HandleTypeDef *AUDIO_Handle = phost->pActiveClass->pData;
  
  if((volume_ctl == VOLUME_UP) || (volume_ctl == VOLUME_DOWN))
  {
    if(phost->gState == HOST_CLASS)
    {
      AUDIO_Handle =  phost->pActiveClass->pData;
      if(AUDIO_Handle->play_state == AUDIO_PLAYBACK_PLAY)
      {
        AUDIO_Handle->control_state = (volume_ctl == VOLUME_UP)? AUDIO_CONTROL_VOLUME_UP : AUDIO_CONTROL_VOLUME_DOWN;
        return USBH_OK;  
      }
    }
  }
  return USBH_FAIL;
}