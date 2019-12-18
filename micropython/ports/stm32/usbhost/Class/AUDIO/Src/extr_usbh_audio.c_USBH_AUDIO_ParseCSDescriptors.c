#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  scalar_t__ uint16_t ;
typedef  size_t int8_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_15__ {scalar_t__ wTotalLength; size_t bNumInterfaces; TYPE_2__* Itf_Desc; } ;
struct TYPE_16__ {TYPE_3__ CfgDesc; scalar_t__ CfgDesc_Raw; } ;
struct TYPE_17__ {TYPE_4__ device; TYPE_1__* pActiveClass; } ;
typedef  TYPE_5__ USBH_HandleTypeDef ;
struct TYPE_18__ {int bDescriptorType; } ;
typedef  TYPE_6__ USBH_DescHeader_t ;
struct TYPE_12__ {scalar_t__ ASNum; scalar_t__ OutputTerminalNum; scalar_t__ InputTerminalNum; scalar_t__ FeatureUnitNum; } ;
struct TYPE_19__ {TYPE_11__ class_desc; } ;
struct TYPE_14__ {int /*<<< orphan*/  bInterfaceSubClass; } ;
struct TYPE_13__ {TYPE_7__* pData; } ;
typedef  TYPE_7__ AUDIO_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  ParseCSDescriptors (TYPE_11__*,int /*<<< orphan*/ ,size_t*) ; 
 size_t USBH_FindInterfaceIndex (TYPE_5__*,size_t,size_t) ; 
 TYPE_6__* USBH_GetNextDesc (void*,scalar_t__*) ; 
 int /*<<< orphan*/  USBH_OK ; 
#define  USB_DESC_TYPE_CS_INTERFACE 129 
#define  USB_DESC_TYPE_INTERFACE 128 
 scalar_t__ USB_LEN_CFG_DESC ; 

__attribute__((used)) static USBH_StatusTypeDef USBH_AUDIO_ParseCSDescriptors(USBH_HandleTypeDef *phost)
{
  USBH_DescHeader_t            *pdesc ;
  uint16_t                      ptr;
  int8_t                        itf_index = 0;
  int8_t                        itf_number = 0; 
  int8_t                        alt_setting;   
  AUDIO_HandleTypeDef           *AUDIO_Handle;
  
  AUDIO_Handle =  phost->pActiveClass->pData;  
  pdesc   = (USBH_DescHeader_t *)(phost->device.CfgDesc_Raw);
  ptr = USB_LEN_CFG_DESC;
  
  AUDIO_Handle->class_desc.FeatureUnitNum = 0;
  AUDIO_Handle->class_desc.InputTerminalNum = 0;
  AUDIO_Handle->class_desc.OutputTerminalNum = 0;  
  AUDIO_Handle->class_desc.ASNum = 0;
  
  while(ptr < phost->device.CfgDesc.wTotalLength)
  {
    pdesc = USBH_GetNextDesc((void *)pdesc, &ptr);
    
    switch (pdesc->bDescriptorType)
    {
      
    case USB_DESC_TYPE_INTERFACE:
      itf_number = *((uint8_t *)pdesc + 2);
      alt_setting = *((uint8_t *)pdesc + 3);
      itf_index = USBH_FindInterfaceIndex (phost, itf_number, alt_setting);     
      break;
      
    case USB_DESC_TYPE_CS_INTERFACE:
      if(itf_number <= phost->device.CfgDesc.bNumInterfaces)
      {
        
        ParseCSDescriptors(&AUDIO_Handle->class_desc,
                           phost->device.CfgDesc.Itf_Desc[itf_index].bInterfaceSubClass, 
                           (uint8_t *)pdesc);
      }
      break;
      
    default:
      break; 
    }
  }
  return USBH_OK;
}