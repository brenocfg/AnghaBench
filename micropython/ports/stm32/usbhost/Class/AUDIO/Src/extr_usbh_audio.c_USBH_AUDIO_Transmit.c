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
struct TYPE_13__ {int Timer; TYPE_1__* pActiveClass; } ;
typedef  TYPE_4__ USBH_HandleTypeDef ;
struct TYPE_12__ {int timer; int buf; int frame_length; int partial_ptr; int global_ptr; int cbuf; int Poll; int total_length; int /*<<< orphan*/  Pipe; } ;
struct TYPE_11__ {int supported; } ;
struct TYPE_14__ {int processing_state; int /*<<< orphan*/  play_state; TYPE_3__ headphone; TYPE_2__ control; } ;
struct TYPE_10__ {TYPE_5__* pData; } ;
typedef  TYPE_5__ AUDIO_HandleTypeDef ;

/* Variables and functions */
#define  AUDIO_DATA_OUT 129 
#define  AUDIO_DATA_START_OUT 128 
 int /*<<< orphan*/  AUDIO_PLAYBACK_IDLE ; 
 int /*<<< orphan*/  USBH_AUDIO_Control (TYPE_4__*) ; 
 int /*<<< orphan*/  USBH_BUSY ; 
 int /*<<< orphan*/  USBH_IsocSendData (TYPE_4__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_LL_GetURBState (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_URB_DONE ; 

__attribute__((used)) static USBH_StatusTypeDef USBH_AUDIO_Transmit (USBH_HandleTypeDef *phost)
{
  USBH_StatusTypeDef status = USBH_BUSY ;
  AUDIO_HandleTypeDef *AUDIO_Handle =  phost->pActiveClass->pData;   
  
  switch(AUDIO_Handle->processing_state)
  {
  case AUDIO_DATA_START_OUT:
    /* Sync with start of Even Frame */
    if((phost->Timer & 1) == 0)
    {
      AUDIO_Handle->headphone.timer = phost->Timer;
      AUDIO_Handle->processing_state = AUDIO_DATA_OUT;
      USBH_IsocSendData(phost, 
                       AUDIO_Handle->headphone.buf,
                       AUDIO_Handle->headphone.frame_length,
                       AUDIO_Handle->headphone.Pipe);
      
      AUDIO_Handle->headphone.partial_ptr = AUDIO_Handle->headphone.frame_length; 
      AUDIO_Handle->headphone.global_ptr = AUDIO_Handle->headphone.frame_length; 
      AUDIO_Handle->headphone.cbuf = AUDIO_Handle->headphone.buf;

    }
    break;
    
  case AUDIO_DATA_OUT:
    if((USBH_LL_GetURBState(phost , AUDIO_Handle->headphone.Pipe) == USBH_URB_DONE)&&
       (( phost->Timer - AUDIO_Handle->headphone.timer) >= AUDIO_Handle->headphone.Poll))
    {
      AUDIO_Handle->headphone.timer = phost->Timer;
      
      if(AUDIO_Handle->control.supported == 1)
      {
        USBH_AUDIO_Control (phost);
      }
      
      if(AUDIO_Handle->headphone.global_ptr <= AUDIO_Handle->headphone.total_length)
      {
        USBH_IsocSendData(phost, 
                          AUDIO_Handle->headphone.cbuf,
                          AUDIO_Handle->headphone.frame_length,
                          AUDIO_Handle->headphone.Pipe);
        
        AUDIO_Handle->headphone.cbuf += AUDIO_Handle->headphone.frame_length;
        AUDIO_Handle->headphone.partial_ptr += AUDIO_Handle->headphone.frame_length;
        AUDIO_Handle->headphone.global_ptr += AUDIO_Handle->headphone.frame_length;
      }
      else
      {
       AUDIO_Handle->headphone.partial_ptr = 0xFFFFFFFF;
       AUDIO_Handle->play_state = AUDIO_PLAYBACK_IDLE;
      }
    }
    break;
  }
  return status;
}