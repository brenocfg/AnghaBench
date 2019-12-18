#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  void* uint16_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_30__ {void* w; } ;
struct TYPE_29__ {void* w; } ;
struct TYPE_28__ {void* w; } ;
struct TYPE_17__ {int bmRequestType; TYPE_9__ wLength; TYPE_8__ wIndex; TYPE_7__ wValue; int /*<<< orphan*/  bRequest; } ;
struct TYPE_18__ {TYPE_10__ b; } ;
struct TYPE_19__ {TYPE_11__ setup; } ;
struct TYPE_20__ {TYPE_12__ Control; TYPE_1__* pActiveClass; } ;
typedef  TYPE_13__ USBH_HandleTypeDef ;
struct TYPE_26__ {TYPE_4__** OutputTerminalDesc; TYPE_3__** FeatureUnitDesc; TYPE_2__** InputTerminalDesc; } ;
struct TYPE_27__ {TYPE_5__ cs_desc; } ;
struct TYPE_25__ {int bTerminalID; } ;
struct TYPE_24__ {int bUnitID; } ;
struct TYPE_23__ {int bTerminalID; } ;
struct TYPE_22__ {TYPE_14__* pData; } ;
struct TYPE_21__ {int* mem; TYPE_6__ class_desc; } ;
typedef  TYPE_14__ AUDIO_HandleTypeDef ;

/* Variables and functions */
 int COPY_PROTECT_CONTROL ; 
#define  UAC_FEATURE_UNIT 130 
 int /*<<< orphan*/  UAC_GET_MIN ; 
#define  UAC_INPUT_TERMINAL 129 
#define  UAC_OUTPUT_TERMINAL 128 
 int /*<<< orphan*/  USBH_CtlReq (TYPE_13__*,int*,void*) ; 
 int USB_D2H ; 
 int USB_REQ_RECIPIENT_INTERFACE ; 
 int USB_REQ_TYPE_CLASS ; 

__attribute__((used)) static USBH_StatusTypeDef USBH_AC_GetMin(USBH_HandleTypeDef *phost, 
                                         uint8_t subtype, 
                                         uint8_t feature,
                                         uint8_t controlSelector,
                                         uint8_t channel,
                                         uint16_t length)
{
  uint16_t wValue = 0, wIndex = 0, wLength = 0;
  uint8_t UnitID = 0, InterfaceNum = 0;
  AUDIO_HandleTypeDef *AUDIO_Handle;
  AUDIO_Handle =  phost->pActiveClass->pData;
  
  switch(subtype)
  {
  case UAC_INPUT_TERMINAL:
    UnitID = AUDIO_Handle->class_desc.cs_desc.InputTerminalDesc[0]->bTerminalID;
    InterfaceNum = 0; /*Always zero Control Interface */
    wIndex = ( UnitID << 8 ) | InterfaceNum ;
    wValue = (COPY_PROTECT_CONTROL << 8 ) ;
    AUDIO_Handle->mem[0] = 0x00;
    
    wLength = 1;
    break;
  case UAC_FEATURE_UNIT:
    UnitID = AUDIO_Handle->class_desc.cs_desc.FeatureUnitDesc[feature]->bUnitID;
    InterfaceNum = 0; /*Always zero Control Interface */
    wIndex = ( UnitID << 8 ) | InterfaceNum ;
    /*holds the CS(control selector ) and CN (channel number)*/
    wValue =  (controlSelector << 8) | channel;
    wLength = length;
    break;
    
  case UAC_OUTPUT_TERMINAL:
    UnitID = AUDIO_Handle->class_desc.cs_desc.OutputTerminalDesc[0]->bTerminalID;
    InterfaceNum = 0; /*Always zero Control Interface */
    wIndex = ( UnitID << 8 ) | InterfaceNum ;
    wValue = (COPY_PROTECT_CONTROL << 8 ) ; 
    wLength = 1; 
    break;
  }
  
  phost->Control.setup.b.bmRequestType = USB_D2H | USB_REQ_RECIPIENT_INTERFACE | \
    USB_REQ_TYPE_CLASS;
  
  phost->Control.setup.b.bRequest = UAC_GET_MIN;
  phost->Control.setup.b.wValue.w = wValue;
  phost->Control.setup.b.wIndex.w = wIndex;
  phost->Control.setup.b.wLength.w = wLength; 
  
  return(USBH_CtlReq(phost, (uint8_t *)(AUDIO_Handle->mem) , wLength ));    
  
}