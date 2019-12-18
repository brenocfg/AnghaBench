#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_7__ {TYPE_1__* pActiveClass; } ;
typedef  TYPE_2__ USBH_HandleTypeDef ;
struct TYPE_8__ {int /*<<< orphan*/ * mem; } ;
struct TYPE_6__ {TYPE_3__* pData; } ;
typedef  TYPE_3__ AUDIO_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  UAC_FEATURE_UNIT ; 
 int /*<<< orphan*/  USBH_AC_SetCur (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USBH_BUSY ; 
 int /*<<< orphan*/  VOLUME_CONTROL ; 

__attribute__((used)) static USBH_StatusTypeDef AUDIO_SetVolume (USBH_HandleTypeDef *phost, uint8_t feature, uint8_t channel, uint16_t volume)
{
  USBH_StatusTypeDef status = USBH_BUSY ;
  AUDIO_HandleTypeDef *AUDIO_Handle; 

  
  AUDIO_Handle = phost->pActiveClass->pData;

  AUDIO_Handle->mem[0] = volume;
  
  status = USBH_AC_SetCur(phost, 
                          UAC_FEATURE_UNIT, 
                          feature,
                          VOLUME_CONTROL,
                          channel,
                          2);
    
  return status; 
}