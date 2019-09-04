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
struct TYPE_7__ {int /*<<< orphan*/ * pUserLineCoding; int /*<<< orphan*/  state; } ;
struct TYPE_5__ {TYPE_3__* pData; } ;
typedef  int /*<<< orphan*/  CDC_LineCodingTypeDef ;
typedef  TYPE_3__ CDC_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  CDC_SET_LINE_CODING_STATE ; 
 scalar_t__ HOST_CLASS ; 
 int /*<<< orphan*/  USBH_OK ; 

USBH_StatusTypeDef USBH_CDC_SetLineCoding(USBH_HandleTypeDef *phost, CDC_LineCodingTypeDef *linecodin)
{
  CDC_HandleTypeDef *CDC_Handle =  phost->pActiveClass->pData;
  if(phost->gState == HOST_CLASS)
  {
    CDC_Handle->state = CDC_SET_LINE_CODING_STATE;
    CDC_Handle->pUserLineCoding = linecodin;    
    
#if (USBH_USE_OS == 1)
    osMessagePut ( phost->os_event, USBH_CLASS_EVENT, 0);
#endif  
  }    
  return USBH_OK;
}