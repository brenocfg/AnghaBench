#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_10__ {TYPE_1__* pActiveClass; } ;
typedef  TYPE_3__ USBH_HandleTypeDef ;
struct TYPE_11__ {int req_state; size_t max_lun; int prev_req_state; TYPE_2__* unit; } ;
struct TYPE_9__ {int /*<<< orphan*/  state_changed; int /*<<< orphan*/  prev_ready_state; } ;
struct TYPE_8__ {TYPE_4__* pData; } ;
typedef  TYPE_4__ MSC_HandleTypeDef ;

/* Variables and functions */
#define  MSC_REQ_ERROR 130 
#define  MSC_REQ_GET_MAX_LUN 129 
#define  MSC_REQ_IDLE 128 
 int /*<<< orphan*/  USBH_BUSY ; 
 int /*<<< orphan*/  USBH_ClrFeature (TYPE_3__*,int) ; 
 int /*<<< orphan*/  USBH_FAIL ; 
 int /*<<< orphan*/  USBH_MSC_BOT_REQ_GetMaxLUN (TYPE_3__*,size_t*) ; 
 int /*<<< orphan*/  USBH_OK ; 
 int /*<<< orphan*/  USBH_UsrLog (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static USBH_StatusTypeDef USBH_MSC_ClassRequest(USBH_HandleTypeDef *phost)
{   
  MSC_HandleTypeDef *MSC_Handle =  phost->pActiveClass->pData;  
  USBH_StatusTypeDef status = USBH_BUSY;
  uint8_t i;
  
  /* Switch MSC REQ state machine */
  switch (MSC_Handle->req_state)
  {
  case MSC_REQ_IDLE:
  case MSC_REQ_GET_MAX_LUN:   
    /* Issue GetMaxLUN request */
    if(USBH_MSC_BOT_REQ_GetMaxLUN(phost, (uint8_t *)&MSC_Handle->max_lun) == USBH_OK )
    {
      MSC_Handle->max_lun = (uint8_t )(MSC_Handle->max_lun) + 1;
      USBH_UsrLog ("Number of supported LUN: %lu", (int32_t)(MSC_Handle->max_lun));
      
      for(i = 0; i < MSC_Handle->max_lun; i++)
      {
        MSC_Handle->unit[i].prev_ready_state = USBH_FAIL;
        MSC_Handle->unit[i].state_changed = 0;
      }
      status = USBH_OK;
    }
    break;
    
  case MSC_REQ_ERROR :
    /* a Clear Feature should be issued here */
    if(USBH_ClrFeature(phost, 0x00) == USBH_OK)
    {
      MSC_Handle->req_state = MSC_Handle->prev_req_state; 
    }    
    break;
    
  default:
    break;
  }
  
  return status; 
}