#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_7__ {int /*<<< orphan*/  pipe_out; int /*<<< orphan*/  pipe_in; } ;
struct TYPE_8__ {TYPE_1__ Control; } ;
typedef  TYPE_2__ USBH_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  USBH_FreePipe (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_LL_DriverVBUS (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_LL_Stop (TYPE_2__*) ; 
 int /*<<< orphan*/  USBH_OK ; 

USBH_StatusTypeDef  USBH_Stop   (USBH_HandleTypeDef *phost)
{
  /* Stop and cleanup the low level driver  */
  USBH_LL_Stop(phost);  
  
  /* DeActivate VBUS on the port */ 
  USBH_LL_DriverVBUS (phost, FALSE);
  
  /* FRee Control Pipes */
  USBH_FreePipe  (phost, phost->Control.pipe_in);
  USBH_FreePipe  (phost, phost->Control.pipe_out);  
  
  return USBH_OK;  
}