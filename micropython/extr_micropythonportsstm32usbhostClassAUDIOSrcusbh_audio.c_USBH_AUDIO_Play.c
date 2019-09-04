#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_8__ {scalar_t__ gState; TYPE_1__* pActiveClass; } ;
typedef  TYPE_3__ USBH_HandleTypeDef ;
struct TYPE_7__ {int /*<<< orphan*/  total_length; int /*<<< orphan*/ * buf; } ;
struct TYPE_9__ {scalar_t__ play_state; int /*<<< orphan*/  processing_state; int /*<<< orphan*/  control_state; TYPE_2__ headphone; } ;
struct TYPE_6__ {TYPE_4__* pData; } ;
typedef  TYPE_4__ AUDIO_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_CONTROL_INIT ; 
 int /*<<< orphan*/  AUDIO_DATA_START_OUT ; 
 scalar_t__ AUDIO_PLAYBACK_IDLE ; 
 scalar_t__ AUDIO_PLAYBACK_PLAY ; 
 scalar_t__ HOST_CLASS ; 
 int /*<<< orphan*/  USBH_FAIL ; 
 int /*<<< orphan*/  USBH_OK ; 

USBH_StatusTypeDef USBH_AUDIO_Play (USBH_HandleTypeDef *phost, uint8_t *buf, uint32_t length)
{
  USBH_StatusTypeDef Status = USBH_FAIL;
  AUDIO_HandleTypeDef *AUDIO_Handle; 
  
  if(phost->gState == HOST_CLASS)
  {
    AUDIO_Handle =  phost->pActiveClass->pData;
    if(AUDIO_Handle->play_state == AUDIO_PLAYBACK_IDLE)
    {
      AUDIO_Handle->headphone.buf = buf;
      AUDIO_Handle->headphone.total_length = length;
      AUDIO_Handle->play_state = AUDIO_PLAYBACK_PLAY;
      AUDIO_Handle->control_state = AUDIO_CONTROL_INIT;
      AUDIO_Handle->processing_state = AUDIO_DATA_START_OUT;
      Status = USBH_OK;
    }
  }
  return Status;  
}