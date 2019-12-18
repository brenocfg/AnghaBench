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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_9__ {scalar_t__ gState; TYPE_1__* pActiveClass; } ;
typedef  TYPE_3__ USBH_HandleTypeDef ;
struct TYPE_8__ {int /*<<< orphan*/  InPipe; } ;
struct TYPE_10__ {TYPE_2__ DataItf; } ;
struct TYPE_7__ {TYPE_4__* pData; } ;
typedef  TYPE_4__ CDC_HandleTypeDef ;

/* Variables and functions */
 scalar_t__ HOST_CLASS ; 
 int /*<<< orphan*/  USBH_LL_GetLastXferSize (TYPE_3__*,int /*<<< orphan*/ ) ; 

uint16_t USBH_CDC_GetLastReceivedDataSize(USBH_HandleTypeDef *phost)
{
  CDC_HandleTypeDef *CDC_Handle =  phost->pActiveClass->pData; 
  
  if(phost->gState == HOST_CLASS)
  {
    return USBH_LL_GetLastXferSize(phost, CDC_Handle->DataItf.InPipe);;
  }
  else
  {
    return 0;
  }
}