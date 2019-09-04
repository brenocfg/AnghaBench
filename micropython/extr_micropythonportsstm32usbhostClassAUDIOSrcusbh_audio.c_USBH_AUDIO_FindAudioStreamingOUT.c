#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_13__ {TYPE_3__* Itf_Desc; } ;
struct TYPE_14__ {TYPE_4__ CfgDesc; } ;
struct TYPE_16__ {TYPE_5__ device; TYPE_1__* pActiveClass; } ;
typedef  TYPE_7__ USBH_HandleTypeDef ;
struct TYPE_17__ {TYPE_6__* stream_out; } ;
struct TYPE_15__ {int Ep; scalar_t__ EpSize; int valid; int /*<<< orphan*/  Poll; int /*<<< orphan*/  AltSettings; int /*<<< orphan*/  interface; } ;
struct TYPE_12__ {scalar_t__ bInterfaceClass; scalar_t__ bInterfaceSubClass; TYPE_2__* Ep_Desc; int /*<<< orphan*/  bAlternateSetting; int /*<<< orphan*/  bInterfaceNumber; } ;
struct TYPE_11__ {int bEndpointAddress; scalar_t__ wMaxPacketSize; int /*<<< orphan*/  bInterval; } ;
struct TYPE_10__ {TYPE_8__* pData; } ;
typedef  TYPE_8__ AUDIO_HandleTypeDef ;

/* Variables and functions */
 scalar_t__ AC_CLASS ; 
 int /*<<< orphan*/  USBH_FAIL ; 
 size_t USBH_MAX_NUM_INTERFACES ; 
 int /*<<< orphan*/  USBH_OK ; 
 scalar_t__ USB_SUBCLASS_AUDIOSTREAMING ; 

__attribute__((used)) static USBH_StatusTypeDef USBH_AUDIO_FindAudioStreamingOUT(USBH_HandleTypeDef *phost)
{
  uint8_t interface, alt_settings;
  USBH_StatusTypeDef status = USBH_FAIL ;
  AUDIO_HandleTypeDef *AUDIO_Handle;

  AUDIO_Handle =  phost->pActiveClass->pData; 

  /* Look For AUDIOSTREAMING IN interface */
  alt_settings = 0;
  for (interface = 0;  interface < USBH_MAX_NUM_INTERFACES ; interface ++ )
  {
    if((phost->device.CfgDesc.Itf_Desc[interface].bInterfaceClass == AC_CLASS)&&
       (phost->device.CfgDesc.Itf_Desc[interface].bInterfaceSubClass == USB_SUBCLASS_AUDIOSTREAMING))
    {
      if(((phost->device.CfgDesc.Itf_Desc[interface].Ep_Desc[0].bEndpointAddress & 0x80) == 0x00)&&
         (phost->device.CfgDesc.Itf_Desc[interface].Ep_Desc[0].wMaxPacketSize > 0))        
      {
        AUDIO_Handle->stream_out[alt_settings].Ep = phost->device.CfgDesc.Itf_Desc[interface].Ep_Desc[0].bEndpointAddress;
        AUDIO_Handle->stream_out[alt_settings].EpSize = phost->device.CfgDesc.Itf_Desc[interface].Ep_Desc[0].wMaxPacketSize;
        AUDIO_Handle->stream_out[alt_settings].interface = phost->device.CfgDesc.Itf_Desc[interface].bInterfaceNumber;
        AUDIO_Handle->stream_out[alt_settings].AltSettings = phost->device.CfgDesc.Itf_Desc[interface].bAlternateSetting;
        AUDIO_Handle->stream_out[alt_settings].Poll = phost->device.CfgDesc.Itf_Desc[interface].Ep_Desc[0].bInterval;           
        AUDIO_Handle->stream_out[alt_settings].valid = 1; 
        alt_settings++;
      }
    }
  }
  
  if(alt_settings > 0)
  {
     status = USBH_OK;
  }
  
  return status;  
}