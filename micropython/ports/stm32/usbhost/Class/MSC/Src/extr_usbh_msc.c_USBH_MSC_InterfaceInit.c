#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_18__ {TYPE_3__* Itf_Desc; } ;
struct TYPE_19__ {size_t current_interface; int /*<<< orphan*/  speed; int /*<<< orphan*/  address; TYPE_4__ CfgDesc; } ;
struct TYPE_20__ {TYPE_5__ device; TYPE_1__* pActiveClass; } ;
typedef  TYPE_6__ USBH_HandleTypeDef ;
struct TYPE_21__ {int InEp; int OutEp; void* OutPipe; void* InPipe; int /*<<< orphan*/  InEpSize; int /*<<< orphan*/  OutEpSize; int /*<<< orphan*/  unit; int /*<<< orphan*/  req_state; int /*<<< orphan*/  error; int /*<<< orphan*/  state; scalar_t__ rw_lun; scalar_t__ current_lun; } ;
struct TYPE_17__ {TYPE_2__* Ep_Desc; } ;
struct TYPE_16__ {int bEndpointAddress; int /*<<< orphan*/  wMaxPacketSize; } ;
struct TYPE_15__ {TYPE_7__* pData; int /*<<< orphan*/  Name; int /*<<< orphan*/  ClassCode; } ;
typedef  TYPE_7__ MSC_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  MSC_BOT ; 
 int /*<<< orphan*/  MSC_INIT ; 
 int /*<<< orphan*/  MSC_OK ; 
 int /*<<< orphan*/  MSC_REQ_IDLE ; 
 int /*<<< orphan*/  MSC_TRANSPARENT ; 
 void* USBH_AllocPipe (TYPE_6__*,int) ; 
 int /*<<< orphan*/  USBH_DbgLog (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_FAIL ; 
 int USBH_FindInterface (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_LL_SetToggle (TYPE_6__*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_MSC_BOT_Init (TYPE_6__*) ; 
 int /*<<< orphan*/  USBH_OK ; 
 int /*<<< orphan*/  USBH_OpenPipe (TYPE_6__*,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_SelectInterface (TYPE_6__*,int) ; 
 scalar_t__ USBH_malloc (int) ; 
 int /*<<< orphan*/  USBH_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USB_EP_TYPE_BULK ; 

__attribute__((used)) static USBH_StatusTypeDef USBH_MSC_InterfaceInit (USBH_HandleTypeDef *phost)
{	 
  uint8_t interface = 0; 
  USBH_StatusTypeDef status = USBH_FAIL ;
  MSC_HandleTypeDef *MSC_Handle;
  
  interface = USBH_FindInterface(phost, phost->pActiveClass->ClassCode, MSC_TRANSPARENT, MSC_BOT);
  
  if(interface == 0xFF) /* Not Valid Interface */
  {
    USBH_DbgLog ("Cannot Find the interface for %s class.", phost->pActiveClass->Name);
    status = USBH_FAIL;      
  }
  else
  {
    USBH_SelectInterface (phost, interface);
    
    phost->pActiveClass->pData = (MSC_HandleTypeDef *)USBH_malloc (sizeof(MSC_HandleTypeDef));
    MSC_Handle =  phost->pActiveClass->pData;
    
    if(phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[0].bEndpointAddress & 0x80)
    {
      MSC_Handle->InEp = (phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[0].bEndpointAddress);
      MSC_Handle->InEpSize  = phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[0].wMaxPacketSize;
    }
    else
    {
      MSC_Handle->OutEp = (phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[0].bEndpointAddress);
      MSC_Handle->OutEpSize  = phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[0].wMaxPacketSize;      
    }
    
    if(phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[1].bEndpointAddress & 0x80)
    {
      MSC_Handle->InEp = (phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[1].bEndpointAddress);
      MSC_Handle->InEpSize  = phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[1].wMaxPacketSize;      
    }
    else
    {
      MSC_Handle->OutEp = (phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[1].bEndpointAddress);
      MSC_Handle->OutEpSize  = phost->device.CfgDesc.Itf_Desc[phost->device.current_interface].Ep_Desc[1].wMaxPacketSize;      
    }
    
    MSC_Handle->current_lun = 0;
    MSC_Handle->rw_lun = 0;
    MSC_Handle->state = MSC_INIT;
    MSC_Handle->error = MSC_OK;
    MSC_Handle->req_state = MSC_REQ_IDLE;
    MSC_Handle->OutPipe = USBH_AllocPipe(phost, MSC_Handle->OutEp);
    MSC_Handle->InPipe = USBH_AllocPipe(phost, MSC_Handle->InEp);

    USBH_MSC_BOT_Init(phost);
    
    /* De-Initialize LUNs information */
    USBH_memset(MSC_Handle->unit, 0, sizeof(MSC_Handle->unit));
    
    /* Open the new channels */
    USBH_OpenPipe  (phost,
                    MSC_Handle->OutPipe,
                    MSC_Handle->OutEp,
                    phost->device.address,
                    phost->device.speed,
                    USB_EP_TYPE_BULK,
                    MSC_Handle->OutEpSize);  
    
    USBH_OpenPipe  (phost,
                    MSC_Handle->InPipe,
                    MSC_Handle->InEp,
                    phost->device.address,
                    phost->device.speed,
                    USB_EP_TYPE_BULK,
                    MSC_Handle->InEpSize);     
    
    
    USBH_LL_SetToggle  (phost, MSC_Handle->InPipe,0);
    USBH_LL_SetToggle  (phost, MSC_Handle->OutPipe,0);
    status = USBH_OK; 
  }
  return status;
}