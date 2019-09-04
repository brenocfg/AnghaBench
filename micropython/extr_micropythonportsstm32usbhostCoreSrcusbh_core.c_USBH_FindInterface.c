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
typedef  int uint8_t ;
typedef  size_t int8_t ;
struct TYPE_7__ {int bInterfaceClass; int bInterfaceSubClass; int bInterfaceProtocol; } ;
typedef  TYPE_2__ USBH_InterfaceDescTypeDef ;
struct TYPE_9__ {TYPE_2__* Itf_Desc; } ;
struct TYPE_6__ {TYPE_4__ CfgDesc; } ;
struct TYPE_8__ {TYPE_1__ device; } ;
typedef  TYPE_3__ USBH_HandleTypeDef ;
typedef  TYPE_4__ USBH_CfgDescTypeDef ;

/* Variables and functions */
 size_t USBH_MAX_NUM_INTERFACES ; 

uint8_t  USBH_FindInterface(USBH_HandleTypeDef *phost, uint8_t Class, uint8_t SubClass, uint8_t Protocol)
{
  USBH_InterfaceDescTypeDef    *pif ;
  USBH_CfgDescTypeDef          *pcfg ;
  int8_t                        if_ix = 0;
  
  pif = (USBH_InterfaceDescTypeDef *)0;
  pcfg = &phost->device.CfgDesc;  
  
  if((pif->bInterfaceClass == 0xFF) &&(pif->bInterfaceSubClass == 0xFF) && (pif->bInterfaceProtocol == 0xFF))
  {
    return 0xFF;
  }
  
  while (if_ix < USBH_MAX_NUM_INTERFACES)
  {
    pif = &pcfg->Itf_Desc[if_ix];
    if(((pif->bInterfaceClass == Class) || (Class == 0xFF))&&
       ((pif->bInterfaceSubClass == SubClass) || (SubClass == 0xFF))&&
         ((pif->bInterfaceProtocol == Protocol) || (Protocol == 0xFF)))
    {
      return  if_ix;
    }
    if_ix++;
  }
  return 0xFF;
}