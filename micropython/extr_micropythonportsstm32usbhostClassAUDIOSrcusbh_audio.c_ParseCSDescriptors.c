#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_5__ {int /*<<< orphan*/ ** MixerUnitDesc; int /*<<< orphan*/ ** SelectorUnitDesc; int /*<<< orphan*/ ** FeatureUnitDesc; int /*<<< orphan*/ ** OutputTerminalDesc; int /*<<< orphan*/ ** InputTerminalDesc; int /*<<< orphan*/ * HeaderDesc; } ;
struct TYPE_7__ {size_t ASNum; TYPE_2__* as_desc; int /*<<< orphan*/  MixerUnitNum; TYPE_1__ cs_desc; int /*<<< orphan*/  SelectorUnitNum; int /*<<< orphan*/  FeatureUnitNum; int /*<<< orphan*/  OutputTerminalNum; int /*<<< orphan*/  InputTerminalNum; } ;
struct TYPE_6__ {int /*<<< orphan*/ * FormatTypeDesc; int /*<<< orphan*/ * GeneralDesc; } ;
typedef  int /*<<< orphan*/  AUDIO_SelectorDescTypeDef ;
typedef  int /*<<< orphan*/  AUDIO_OTDescTypeDef ;
typedef  int /*<<< orphan*/  AUDIO_MixerDescTypeDef ;
typedef  int /*<<< orphan*/  AUDIO_ITDescTypeDef ;
typedef  int /*<<< orphan*/  AUDIO_HeaderDescTypeDef ;
typedef  int /*<<< orphan*/  AUDIO_FeatureDescTypeDef ;
typedef  TYPE_3__ AUDIO_ClassSpecificDescTypedef ;
typedef  int /*<<< orphan*/  AUDIO_ASGeneralDescTypeDef ;
typedef  int /*<<< orphan*/  AUDIO_ASFormatTypeDescTypeDef ;

/* Variables and functions */
#define  UAC_AS_GENERAL 135 
#define  UAC_FEATURE_UNIT 134 
#define  UAC_FORMAT_TYPE 133 
#define  UAC_HEADER 132 
#define  UAC_INPUT_TERMINAL 131 
#define  UAC_MIXER_UNIT 130 
#define  UAC_OUTPUT_TERMINAL 129 
#define  UAC_SELECTOR_UNIT 128 
 int /*<<< orphan*/  USBH_OK ; 
 scalar_t__ USB_SUBCLASS_AUDIOCONTROL ; 
 scalar_t__ USB_SUBCLASS_AUDIOSTREAMING ; 

__attribute__((used)) static USBH_StatusTypeDef ParseCSDescriptors(AUDIO_ClassSpecificDescTypedef *class_desc, 
                                      uint8_t ac_subclass, 
                                      uint8_t *pdesc)
{
  if(ac_subclass == USB_SUBCLASS_AUDIOCONTROL)
  {
    switch(pdesc[2])
    {
    case UAC_HEADER: 
      class_desc->cs_desc.HeaderDesc = (AUDIO_HeaderDescTypeDef *)pdesc;    
      break;
      
    case UAC_INPUT_TERMINAL:
      class_desc->cs_desc.InputTerminalDesc[class_desc->InputTerminalNum++] = (AUDIO_ITDescTypeDef*) pdesc;    
      break;
      
    case UAC_OUTPUT_TERMINAL:
      class_desc->cs_desc.OutputTerminalDesc[class_desc->OutputTerminalNum++] = (AUDIO_OTDescTypeDef*) pdesc;   
      break;

    case UAC_FEATURE_UNIT:
      class_desc->cs_desc.FeatureUnitDesc[class_desc->FeatureUnitNum++] = (AUDIO_FeatureDescTypeDef*) pdesc; 
      break;
      
    case UAC_SELECTOR_UNIT:
      class_desc->cs_desc.SelectorUnitDesc[class_desc->SelectorUnitNum++] = (AUDIO_SelectorDescTypeDef*) pdesc; 
      break;

    case UAC_MIXER_UNIT:
      class_desc->cs_desc.MixerUnitDesc[class_desc->MixerUnitNum++] = (AUDIO_MixerDescTypeDef*) pdesc; 
      break;      

    default: 
      break;
    }
  }
  else if(ac_subclass == USB_SUBCLASS_AUDIOSTREAMING)
  {
    switch(pdesc[2])
    {
    case UAC_AS_GENERAL:
      class_desc->as_desc[class_desc->ASNum].GeneralDesc = (AUDIO_ASGeneralDescTypeDef*) pdesc; 
      break;
    case UAC_FORMAT_TYPE:      
      class_desc->as_desc[class_desc->ASNum++].FormatTypeDesc = (AUDIO_ASFormatTypeDescTypeDef*) pdesc; 
      break;
    default:
      break;
    }
  }
 
  return USBH_OK;
}