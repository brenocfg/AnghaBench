#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  void* uint16_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_27__ {void* w; } ;
struct TYPE_26__ {void* w; } ;
struct TYPE_25__ {void* w; } ;
struct TYPE_28__ {int bmRequestType; TYPE_8__ wLength; TYPE_7__ wIndex; TYPE_6__ wValue; int /*<<< orphan*/  bRequest; } ;
struct TYPE_16__ {TYPE_9__ b; } ;
struct TYPE_17__ {TYPE_10__ setup; } ;
struct TYPE_18__ {TYPE_11__ Control; TYPE_1__* pActiveClass; } ;
typedef  TYPE_12__ USBH_HandleTypeDef ;
struct TYPE_23__ {TYPE_3__** FeatureUnitDesc; TYPE_2__** InputTerminalDesc; } ;
struct TYPE_24__ {TYPE_4__ cs_desc; } ;
struct TYPE_22__ {int bUnitID; } ;
struct TYPE_21__ {int bTerminalID; } ;
struct TYPE_20__ {TYPE_13__* pData; } ;
struct TYPE_19__ {int* mem; TYPE_5__ class_desc; } ;
typedef  TYPE_13__ AUDIO_HandleTypeDef ;

/* Variables and functions */
 int COPY_PROTECT_CONTROL ; 
#define  UAC_FEATURE_UNIT 129 
#define  UAC_INPUT_TERMINAL 128 
 int /*<<< orphan*/  UAC_SET_CUR ; 
 int /*<<< orphan*/  USBH_CtlReq (TYPE_12__*,int*,void*) ; 
 int USB_H2D ; 
 int USB_REQ_RECIPIENT_INTERFACE ; 
 int USB_REQ_TYPE_CLASS ; 

__attribute__((used)) static USBH_StatusTypeDef USBH_AC_SetCur(USBH_HandleTypeDef *phost, 
                                         uint8_t subtype, 
                                         uint8_t feature,
                                         uint8_t controlSelector,
                                         uint8_t channel,
                                         uint16_t length)
{
  uint16_t wValue,wIndex,wLength;
  uint8_t UnitID,InterfaceNum;
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
  }
  
  phost->Control.setup.b.bmRequestType = USB_H2D | USB_REQ_RECIPIENT_INTERFACE | \
    USB_REQ_TYPE_CLASS;
  
  phost->Control.setup.b.bRequest = UAC_SET_CUR;
  phost->Control.setup.b.wValue.w = wValue;
  phost->Control.setup.b.wIndex.w = wIndex;
  phost->Control.setup.b.wLength.w = wLength; 
  
  return(USBH_CtlReq(phost, (uint8_t *)(AUDIO_Handle->mem) , wLength ));    
  
}