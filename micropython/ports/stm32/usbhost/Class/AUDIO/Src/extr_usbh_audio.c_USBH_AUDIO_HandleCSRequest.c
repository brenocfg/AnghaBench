#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ USBH_StatusTypeDef ;
struct TYPE_9__ {int /*<<< orphan*/  os_event; TYPE_2__* pActiveClass; } ;
typedef  TYPE_3__ USBH_HandleTypeDef ;
struct TYPE_7__ {int /*<<< orphan*/  asociated_feature; } ;
struct TYPE_10__ {int temp_channels; int /*<<< orphan*/  cs_req_state; TYPE_1__ headphone; int /*<<< orphan*/  temp_feature; } ;
struct TYPE_8__ {TYPE_4__* pData; } ;
typedef  TYPE_4__ AUDIO_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_REQ_GET_VOLUME ; 
 scalar_t__ USBH_AUDIO_CSRequest (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ USBH_BUSY ; 
 scalar_t__ USBH_OK ; 
 int /*<<< orphan*/  USBH_URB_EVENT ; 
 int /*<<< orphan*/  osMessagePut (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static USBH_StatusTypeDef USBH_AUDIO_HandleCSRequest(USBH_HandleTypeDef *phost)
{ 

  USBH_StatusTypeDef status = USBH_BUSY;
  USBH_StatusTypeDef cs_status = USBH_BUSY;
  AUDIO_HandleTypeDef *AUDIO_Handle =  phost->pActiveClass->pData;  
        
  cs_status = USBH_AUDIO_CSRequest(phost, 
                                   AUDIO_Handle->temp_feature, 
                                   AUDIO_Handle->temp_channels);
  
  if(cs_status != USBH_BUSY)
  {
    
    if(AUDIO_Handle->temp_channels ==  1)
    {
        AUDIO_Handle->temp_feature = AUDIO_Handle->headphone.asociated_feature;
        AUDIO_Handle->temp_channels = 0;
        status = USBH_OK; 
    }
    else
    {
      AUDIO_Handle->temp_channels--;
    }
    AUDIO_Handle->cs_req_state = AUDIO_REQ_GET_VOLUME;
#if (USBH_USE_OS == 1)
      osMessagePut ( phost->os_event, USBH_URB_EVENT, 0);
#endif     
  }
  
  return status;
}