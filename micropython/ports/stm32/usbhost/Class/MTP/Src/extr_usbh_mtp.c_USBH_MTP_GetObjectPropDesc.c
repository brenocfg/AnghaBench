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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_7__ {scalar_t__ is_connected; } ;
struct TYPE_9__ {scalar_t__ Timer; TYPE_1__ device; TYPE_2__* pActiveClass; } ;
typedef  TYPE_3__ USBH_HandleTypeDef ;
struct TYPE_10__ {scalar_t__ is_ready; } ;
struct TYPE_8__ {TYPE_4__* pData; } ;
typedef  int /*<<< orphan*/  PTP_ObjectPropDescTypeDef ;
typedef  TYPE_4__ MTP_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USBH_BUSY ; 
 int /*<<< orphan*/  USBH_FAIL ; 
 int /*<<< orphan*/  USBH_PTP_GetObjectPropDesc (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

USBH_StatusTypeDef USBH_MTP_GetObjectPropDesc (USBH_HandleTypeDef *phost,
                                                uint16_t opc, 
                                                uint16_t ofc, 
                                                PTP_ObjectPropDescTypeDef *opd)
{
  USBH_StatusTypeDef status = USBH_FAIL;
  MTP_HandleTypeDef *MTP_Handle =  phost->pActiveClass->pData;
  uint32_t timeout = phost->Timer + 5000;
  
  if(MTP_Handle->is_ready)
  {   
    while ((status = USBH_PTP_GetObjectPropDesc (phost,
                                                opc, 
                                                ofc, 
                                                opd)) == USBH_BUSY)
    {
      if((phost->Timer > timeout) || (phost->device.is_connected == 0)) 
      {
        return USBH_FAIL;
      }
    }
  }
  return status; 
}