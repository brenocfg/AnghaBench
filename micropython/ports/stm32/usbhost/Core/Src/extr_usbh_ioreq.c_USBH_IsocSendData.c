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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
typedef  int /*<<< orphan*/  USBH_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USBH_EP_ISO ; 
 int /*<<< orphan*/  USBH_LL_SubmitURB (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_OK ; 
 int /*<<< orphan*/  USBH_PID_DATA ; 

USBH_StatusTypeDef USBH_IsocSendData(USBH_HandleTypeDef *phost, 
                                uint8_t *buff, 
                                uint32_t length,
                                uint8_t pipe_num)
{
  USBH_LL_SubmitURB (phost,         /* Driver handle    */
                          pipe_num,             /* Pipe index       */
                          0,                    /* Direction : OUT   */
                          USBH_EP_ISO,          /* EP type          */                          
                          USBH_PID_DATA,        /* Type Data        */
                          buff,                 /* data buffer      */
                          length,               /* data length      */ 
                          0);
  
  return USBH_OK;
}