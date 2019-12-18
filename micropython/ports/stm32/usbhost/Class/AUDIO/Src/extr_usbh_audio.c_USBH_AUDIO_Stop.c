#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
typedef  int /*<<< orphan*/  USBH_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USBH_AUDIO_Suspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USBH_FAIL ; 

USBH_StatusTypeDef USBH_AUDIO_Stop (USBH_HandleTypeDef *phost)
{
  USBH_StatusTypeDef Status = USBH_FAIL;
  Status = USBH_AUDIO_Suspend(phost);
  return Status;  
}