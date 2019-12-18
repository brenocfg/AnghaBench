#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_15__ {TYPE_1__* pActiveClass; } ;
typedef  TYPE_6__ USBH_HandleTypeDef ;
struct TYPE_14__ {size_t asociated_feature; size_t asociated_mixer; size_t asociated_selector; size_t asociated_terminal; int /*<<< orphan*/  asociated_channels; } ;
struct TYPE_12__ {TYPE_2__** InputTerminalDesc; } ;
struct TYPE_13__ {size_t InputTerminalNum; TYPE_3__ cs_desc; } ;
struct TYPE_16__ {TYPE_5__ microphone; TYPE_4__ class_desc; } ;
struct TYPE_11__ {size_t bTerminalID; int /*<<< orphan*/  bNrChannels; int /*<<< orphan*/  wTerminalType; } ;
struct TYPE_10__ {TYPE_7__* pData; } ;
typedef  TYPE_7__ AUDIO_HandleTypeDef ;

/* Variables and functions */
 int LE16 (int /*<<< orphan*/ ) ; 
#define  UAC_FEATURE_UNIT 131 
#define  UAC_MIXER_UNIT 130 
#define  UAC_OUTPUT_TERMINAL 129 
#define  UAC_SELECTOR_UNIT 128 
 int USBH_AUDIO_FindLinkedUnit (TYPE_6__*,size_t) ; 
 int /*<<< orphan*/  USBH_OK ; 

USBH_StatusTypeDef USBH_AUDIO_BuildMicrophonePath(USBH_HandleTypeDef *phost)
{
  uint8_t UnitID = 0, Type, Index;
  uint32_t value;
  uint8_t terminalIndex;  
  AUDIO_HandleTypeDef *AUDIO_Handle;
  
  AUDIO_Handle =  phost->pActiveClass->pData;    
  
  /*Find microphone IT*/
  for(terminalIndex = 0; terminalIndex < AUDIO_Handle->class_desc.InputTerminalNum; terminalIndex++)
  {
    if(LE16(AUDIO_Handle->class_desc.cs_desc.InputTerminalDesc[terminalIndex]->wTerminalType) == 0x201)
    {    
      UnitID = AUDIO_Handle->class_desc.cs_desc.InputTerminalDesc[terminalIndex]->bTerminalID;
      AUDIO_Handle->microphone.asociated_channels =  AUDIO_Handle->class_desc.cs_desc.InputTerminalDesc[terminalIndex]->bNrChannels;
      break;
    }
  }
  
  do
  {
    value =  USBH_AUDIO_FindLinkedUnit(phost, UnitID);
    Index = value & 0xFF;
    Type   = (value >> 8) & 0xFF;
    UnitID   = (value >> 16) & 0xFF;
    
    switch (Type)
    {
    case UAC_FEATURE_UNIT:
      AUDIO_Handle->microphone.asociated_feature = Index;
      break;
      
    case UAC_MIXER_UNIT:
      AUDIO_Handle->microphone.asociated_mixer = Index;
      break;
      
    case UAC_SELECTOR_UNIT:
      AUDIO_Handle->microphone.asociated_selector = Index;
      break;
      
    case UAC_OUTPUT_TERMINAL:
      AUDIO_Handle->microphone.asociated_terminal = Index;
      break;    
    }
  }
  while ((Type != UAC_OUTPUT_TERMINAL) && (value > 0));
  
  
  
  return USBH_OK;
}