#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_12__ {TYPE_1__* pActiveClass; } ;
typedef  TYPE_4__ USBH_HandleTypeDef ;
struct TYPE_11__ {int supported; } ;
struct TYPE_10__ {int supported; } ;
struct TYPE_13__ {TYPE_3__ microphone; TYPE_2__ headphone; } ;
struct TYPE_9__ {TYPE_5__* pData; } ;
typedef  TYPE_5__ AUDIO_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USBH_AUDIO_InputStream (TYPE_4__*) ; 
 int /*<<< orphan*/  USBH_AUDIO_OutputStream (TYPE_4__*) ; 
 int /*<<< orphan*/  USBH_BUSY ; 

__attribute__((used)) static USBH_StatusTypeDef USBH_AUDIO_Process (USBH_HandleTypeDef *phost)
{   
  USBH_StatusTypeDef status = USBH_BUSY;
  AUDIO_HandleTypeDef *AUDIO_Handle =  phost->pActiveClass->pData;  
  
  if(AUDIO_Handle->headphone.supported == 1)
  {
    USBH_AUDIO_OutputStream (phost);
  }
  
  if(AUDIO_Handle->microphone.supported == 1)
  {
    USBH_AUDIO_InputStream (phost);
  }
 
  return status;
}