#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_14__ {TYPE_1__* pActiveClass; } ;
typedef  TYPE_4__ USBH_HandleTypeDef ;
struct TYPE_12__ {int volumeMin; int volumeMax; void* resolution; void* volume; } ;
struct TYPE_13__ {TYPE_2__ attribute; } ;
struct TYPE_15__ {int cs_req_state; int /*<<< orphan*/ * mem; TYPE_3__ headphone; } ;
struct TYPE_11__ {TYPE_5__* pData; } ;
typedef  TYPE_5__ AUDIO_HandleTypeDef ;

/* Variables and functions */
#define  AUDIO_REQ_CS_IDLE 132 
#define  AUDIO_REQ_GET_MAX_VOLUME 131 
#define  AUDIO_REQ_GET_MIN_VOLUME 130 
#define  AUDIO_REQ_GET_RESOLUTION 129 
#define  AUDIO_REQ_GET_VOLUME 128 
 void* LE16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UAC_FEATURE_UNIT ; 
 int /*<<< orphan*/  USBH_AC_GetCur (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USBH_AC_GetMax (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USBH_AC_GetMin (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USBH_AC_GetRes (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USBH_BUSY ; 
 int /*<<< orphan*/  USBH_OK ; 
 int /*<<< orphan*/  VOLUME_CONTROL ; 

__attribute__((used)) static USBH_StatusTypeDef USBH_AUDIO_CSRequest(USBH_HandleTypeDef *phost, uint8_t feature, uint8_t channel)
{   
  AUDIO_HandleTypeDef *AUDIO_Handle =  phost->pActiveClass->pData;  
  USBH_StatusTypeDef status = USBH_BUSY;
  USBH_StatusTypeDef req_status = USBH_BUSY;
  
  /* Switch AUDIO REQ state machine */
  switch (AUDIO_Handle->cs_req_state)
  {
  case AUDIO_REQ_GET_VOLUME:
    req_status = USBH_AC_GetCur(phost,                 
                                UAC_FEATURE_UNIT,     /* subtype  */
                                feature,              /* feature  */
                                VOLUME_CONTROL,       /* Selector */
                                channel,              /* channel  */
                                0x02);                /* length   */
    if(req_status != USBH_BUSY)
    {
      AUDIO_Handle->cs_req_state = AUDIO_REQ_GET_MIN_VOLUME;
      AUDIO_Handle->headphone.attribute.volume = LE16(&(AUDIO_Handle->mem[0]));
    }
    break;
    
  case AUDIO_REQ_GET_MIN_VOLUME:
    req_status = USBH_AC_GetMin(phost,                 
                                UAC_FEATURE_UNIT,     /* subtype  */
                                feature,              /* feature  */
                                VOLUME_CONTROL,       /* Selector */
                                channel,              /* channel  */
                                0x02);                /* length   */
    if(req_status != USBH_BUSY)
    {
      AUDIO_Handle->cs_req_state = AUDIO_REQ_GET_MAX_VOLUME;
      AUDIO_Handle->headphone.attribute.volumeMin = LE16(&AUDIO_Handle->mem[0]);
    }
    break;

  case AUDIO_REQ_GET_MAX_VOLUME:
    req_status = USBH_AC_GetMax(phost,                 
                                UAC_FEATURE_UNIT,     /* subtype  */
                                feature,              /* feature  */
                                VOLUME_CONTROL,       /* Selector */
                                channel,              /* channel  */
                                0x02);                /* length   */
    if(req_status != USBH_BUSY)
    {
      AUDIO_Handle->cs_req_state = AUDIO_REQ_GET_RESOLUTION;
      AUDIO_Handle->headphone.attribute.volumeMax = LE16(&AUDIO_Handle->mem[0]);   
      
      if (AUDIO_Handle->headphone.attribute.volumeMax < AUDIO_Handle->headphone.attribute.volumeMin)
      {
        AUDIO_Handle->headphone.attribute.volumeMax = 0xFF00; 
      }
    }
    break;
    
  case AUDIO_REQ_GET_RESOLUTION:
    req_status = USBH_AC_GetRes(phost,                 
                                UAC_FEATURE_UNIT,     /* subtype  */
                                feature,              /* feature  */
                                VOLUME_CONTROL,       /* Selector */
                                channel,              /* channel  */
                                0x02);                /* length   */
    if(req_status != USBH_BUSY)
    {
      AUDIO_Handle->cs_req_state = AUDIO_REQ_CS_IDLE;
      AUDIO_Handle->headphone.attribute.resolution = LE16(&AUDIO_Handle->mem[0]);    
    }
    break;
    
 
  case AUDIO_REQ_CS_IDLE:
    status = USBH_OK;
  default:
    break;
  }
  return status; 
}