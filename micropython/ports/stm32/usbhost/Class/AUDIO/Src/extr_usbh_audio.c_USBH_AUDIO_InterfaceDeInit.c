#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_15__ {TYPE_4__* pActiveClass; } ;
typedef  TYPE_5__ USBH_HandleTypeDef ;
struct TYPE_13__ {int Pipe; } ;
struct TYPE_12__ {int Pipe; } ;
struct TYPE_11__ {int Pipe; } ;
struct TYPE_16__ {TYPE_3__ control; TYPE_2__ headphone; TYPE_1__ microphone; } ;
struct TYPE_14__ {TYPE_6__* pData; } ;
typedef  TYPE_6__ AUDIO_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USBH_ClosePipe (TYPE_5__*,int) ; 
 int /*<<< orphan*/  USBH_FreePipe (TYPE_5__*,int) ; 
 int /*<<< orphan*/  USBH_OK ; 
 int /*<<< orphan*/  USBH_free (TYPE_6__*) ; 

USBH_StatusTypeDef USBH_AUDIO_InterfaceDeInit (USBH_HandleTypeDef *phost)
{
  AUDIO_HandleTypeDef *AUDIO_Handle =  phost->pActiveClass->pData; 
  
  if(AUDIO_Handle->microphone.Pipe != 0x00)
  {   
    USBH_ClosePipe  (phost, AUDIO_Handle->microphone.Pipe);
    USBH_FreePipe  (phost, AUDIO_Handle->microphone.Pipe);
    AUDIO_Handle->microphone.Pipe = 0;     /* Reset the pipe as Free */  
  }
  
  if( AUDIO_Handle->headphone.Pipe != 0x00)
  {   
    USBH_ClosePipe(phost,  AUDIO_Handle->headphone.Pipe);
    USBH_FreePipe  (phost,  AUDIO_Handle->headphone.Pipe);
    AUDIO_Handle->headphone.Pipe = 0;     /* Reset the pipe as Free */  
  }
  
  if( AUDIO_Handle->control.Pipe != 0x00)
  {   
    USBH_ClosePipe(phost,  AUDIO_Handle->control.Pipe);
    USBH_FreePipe  (phost,  AUDIO_Handle->control.Pipe);
    AUDIO_Handle->control.Pipe = 0;     /* Reset the pipe as Free */  
  }
  
  if(phost->pActiveClass->pData)
  {
    USBH_free (phost->pActiveClass->pData);
    phost->pActiveClass->pData = 0;
  }  
  return USBH_OK ;
}