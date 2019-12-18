#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_17__ {TYPE_3__* Itf_Desc; } ;
struct TYPE_18__ {size_t current_interface; int /*<<< orphan*/  speed; int /*<<< orphan*/  address; TYPE_4__ CfgDesc; } ;
struct TYPE_19__ {TYPE_5__ device; TYPE_1__* pActiveClass; } ;
typedef  TYPE_6__ USBH_HandleTypeDef ;
struct TYPE_20__ {int ep_addr; scalar_t__ poll; int InEp; int OutEp; void* OutPipe; int /*<<< orphan*/  length; void* InPipe; int /*<<< orphan*/  ctl_state; int /*<<< orphan*/  state; int /*<<< orphan*/  Init; } ;
struct TYPE_16__ {scalar_t__ bInterfaceProtocol; scalar_t__ bNumEndpoints; TYPE_2__* Ep_Desc; } ;
struct TYPE_15__ {int bEndpointAddress; scalar_t__ bInterval; int /*<<< orphan*/  wMaxPacketSize; } ;
struct TYPE_14__ {TYPE_7__* pData; int /*<<< orphan*/  Name; int /*<<< orphan*/  ClassCode; } ;
typedef  TYPE_7__ HID_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  HID_BOOT_CODE ; 
 int /*<<< orphan*/  HID_ERROR ; 
 int /*<<< orphan*/  HID_INIT ; 
 scalar_t__ HID_KEYBRD_BOOT_CODE ; 
 scalar_t__ HID_MIN_POLL ; 
 scalar_t__ HID_MOUSE_BOOT_CODE ; 
 int /*<<< orphan*/  HID_REQ_INIT ; 
 void* USBH_AllocPipe (TYPE_6__*,int) ; 
 int /*<<< orphan*/  USBH_DbgLog (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_FAIL ; 
 int USBH_FindInterface (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USBH_HID_KeybdInit ; 
 int /*<<< orphan*/  USBH_HID_MouseInit ; 
 int /*<<< orphan*/  USBH_LL_SetToggle (TYPE_6__*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ USBH_MAX_NUM_ENDPOINTS ; 
 int /*<<< orphan*/  USBH_OK ; 
 int /*<<< orphan*/  USBH_OpenPipe (TYPE_6__*,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_SelectInterface (TYPE_6__*,int) ; 
 int /*<<< orphan*/  USBH_UsrLog (char*) ; 
 scalar_t__ USBH_malloc (int) ; 
 int /*<<< orphan*/  USB_EP_TYPE_INTR ; 

__attribute__((used)) static USBH_StatusTypeDef USBH_HID_InterfaceInit (USBH_HandleTypeDef *phost)
{	
  uint8_t max_ep;
  uint8_t num = 0;
  uint8_t interface;
  
  USBH_StatusTypeDef status = USBH_FAIL ;
  HID_HandleTypeDef *HID_Handle;
  
  interface = USBH_FindInterface(phost, phost->pActiveClass->ClassCode, HID_BOOT_CODE, 0xFF);
  
  if(interface == 0xFF) /* No Valid Interface */
  {
    status = USBH_FAIL;  
    USBH_DbgLog ("Cannot Find the interface for %s class.", phost->pActiveClass->Name);         
  }
  else
  {
    USBH_SelectInterface (phost, interface);
    phost->pActiveClass->pData = (HID_HandleTypeDef *)USBH_malloc (sizeof(HID_HandleTypeDef));
    HID_Handle =  phost->pActiveClass->pData; 
    HID_Handle->state = HID_ERROR;
    
    /*Decode Bootclass Protocl: Mouse or Keyboard*/
    if(phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].bInterfaceProtocol == HID_KEYBRD_BOOT_CODE)
    {
      USBH_UsrLog ("KeyBoard device found!"); 
      HID_Handle->Init =  USBH_HID_KeybdInit;     
    }
    else if(phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].bInterfaceProtocol  == HID_MOUSE_BOOT_CODE)		  
    {
      USBH_UsrLog ("Mouse device found!");         
      HID_Handle->Init =  USBH_HID_MouseInit;     
    }
    else
    {
      USBH_UsrLog ("Protocol not supported.");  
      return USBH_FAIL;
    }
    
    HID_Handle->state     = HID_INIT;
    HID_Handle->ctl_state = HID_REQ_INIT; 
    HID_Handle->ep_addr   = phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[0].bEndpointAddress;
    HID_Handle->length    = phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[0].wMaxPacketSize;
    HID_Handle->poll      = phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[0].bInterval ;
    
    if (HID_Handle->poll  < HID_MIN_POLL) 
    {
      HID_Handle->poll = HID_MIN_POLL;
    }
    
    /* Check fo available number of endpoints */
    /* Find the number of EPs in the Interface Descriptor */      
    /* Choose the lower number in order not to overrun the buffer allocated */
    max_ep = ( (phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].bNumEndpoints <= USBH_MAX_NUM_ENDPOINTS) ? 
              phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].bNumEndpoints :
                  USBH_MAX_NUM_ENDPOINTS); 
    
    
    /* Decode endpoint IN and OUT address from interface descriptor */
    for ( ;num < max_ep; num++)
    {
      if(phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[num].bEndpointAddress & 0x80)
      {
        HID_Handle->InEp = (phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[num].bEndpointAddress);
        HID_Handle->InPipe  =\
          USBH_AllocPipe(phost, HID_Handle->InEp);
        
        /* Open pipe for IN endpoint */
        USBH_OpenPipe  (phost,
                        HID_Handle->InPipe,
                        HID_Handle->InEp,
                        phost->device.address,
                        phost->device.speed,
                        USB_EP_TYPE_INTR,
                        HID_Handle->length); 
        
        USBH_LL_SetToggle (phost, HID_Handle->InPipe, 0);
        
      }
      else
      {
        HID_Handle->OutEp = (phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[num].bEndpointAddress);
        HID_Handle->OutPipe  =\
          USBH_AllocPipe(phost, HID_Handle->OutEp);
        
        /* Open pipe for OUT endpoint */
        USBH_OpenPipe  (phost,
                        HID_Handle->OutPipe,
                        HID_Handle->OutEp,                            
                        phost->device.address,
                        phost->device.speed,
                        USB_EP_TYPE_INTR,
                        HID_Handle->length); 
        
        USBH_LL_SetToggle (phost, HID_Handle->OutPipe, 0);        
      }
      
    }  
    status = USBH_OK;
  }
  return status;
}