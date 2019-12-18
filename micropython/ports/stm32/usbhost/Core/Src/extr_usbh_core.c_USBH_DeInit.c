#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_7__ {TYPE_1__* pActiveClass; int /*<<< orphan*/ * pData; } ;
typedef  TYPE_2__ USBH_HandleTypeDef ;
struct TYPE_6__ {int /*<<< orphan*/ * pData; } ;

/* Variables and functions */
 int /*<<< orphan*/  DeInitStateMachine (TYPE_2__*) ; 
 int /*<<< orphan*/  USBH_LL_Stop (TYPE_2__*) ; 
 int /*<<< orphan*/  USBH_OK ; 

USBH_StatusTypeDef  USBH_DeInit(USBH_HandleTypeDef *phost)
{
  DeInitStateMachine(phost);
  
  if(phost->pData != NULL)
  {
    phost->pActiveClass->pData = NULL;
    USBH_LL_Stop(phost);
  }

  return USBH_OK;
}