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
typedef  size_t uint8_t ;
struct TYPE_8__ {scalar_t__ gState; TYPE_1__* pActiveClass; } ;
typedef  TYPE_3__ USBH_HandleTypeDef ;
struct TYPE_9__ {TYPE_2__* unit; } ;
struct TYPE_7__ {scalar_t__ error; } ;
struct TYPE_6__ {TYPE_4__* pData; } ;
typedef  TYPE_4__ MSC_HandleTypeDef ;

/* Variables and functions */
 scalar_t__ HOST_CLASS ; 
 scalar_t__ MSC_OK ; 

uint8_t  USBH_MSC_UnitIsReady (USBH_HandleTypeDef *phost, uint8_t lun)
{
  MSC_HandleTypeDef *MSC_Handle =  phost->pActiveClass->pData;  
  
  if(phost->gState == HOST_CLASS)
  {
    return (MSC_Handle->unit[lun].error == MSC_OK);
  }
  else
  {
    return 0;
  }
}