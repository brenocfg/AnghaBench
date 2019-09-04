#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_9__ {TYPE_2__* Itf_Desc; } ;
struct TYPE_10__ {TYPE_3__ CfgDesc; } ;
struct TYPE_11__ {TYPE_4__ device; } ;
typedef  TYPE_5__ USBH_HandleTypeDef ;
struct TYPE_8__ {scalar_t__ bInterfaceClass; TYPE_1__* Ep_Desc; } ;
struct TYPE_7__ {int bEndpointAddress; scalar_t__ wMaxPacketSize; int bmAttributes; } ;

/* Variables and functions */
 int USBH_EP_BULK ; 
 size_t USBH_MAX_NUM_ENDPOINTS ; 
 size_t USBH_MAX_NUM_INTERFACES ; 
 scalar_t__ USB_MTP_CLASS ; 

__attribute__((used)) static uint8_t MTP_FindDataInEndpoint(USBH_HandleTypeDef *phost)
{
  uint8_t interface, endpoint;
  
  for (interface = 0;  interface < USBH_MAX_NUM_INTERFACES ; interface ++ )
  {
    if(phost->device.CfgDesc.Itf_Desc[interface].bInterfaceClass == USB_MTP_CLASS)
    {    
      for (endpoint = 0;  endpoint < USBH_MAX_NUM_ENDPOINTS ; endpoint ++ )
      {
        
        if((phost->device.CfgDesc.Itf_Desc[interface].Ep_Desc[endpoint].bEndpointAddress & 0x80)&&
           (phost->device.CfgDesc.Itf_Desc[interface].Ep_Desc[endpoint].wMaxPacketSize > 0)&&
             ((phost->device.CfgDesc.Itf_Desc[interface].Ep_Desc[endpoint].bmAttributes & USBH_EP_BULK) == USBH_EP_BULK))
        {
          return endpoint;
        }
      }
    }
  }
  
  return 0xFF; /* Invalid Endpoint */
}