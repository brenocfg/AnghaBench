#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_3__ {scalar_t__ ClassNumber; int /*<<< orphan*/ ** pClass; } ;
typedef  TYPE_1__ USBH_HandleTypeDef ;
typedef  int /*<<< orphan*/  USBH_ClassTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USBH_ErrLog (char*) ; 
 int /*<<< orphan*/  USBH_FAIL ; 
 scalar_t__ USBH_MAX_NUM_SUPPORTED_CLASS ; 
 int /*<<< orphan*/  USBH_OK ; 

USBH_StatusTypeDef  USBH_RegisterClass(USBH_HandleTypeDef *phost, USBH_ClassTypeDef *pclass)
{
  USBH_StatusTypeDef   status = USBH_OK;
  
  if(pclass != 0)
  {
    if(phost->ClassNumber < USBH_MAX_NUM_SUPPORTED_CLASS)
    {
      /* link the class tgo the USB Host handle */
      phost->pClass[phost->ClassNumber++] = pclass;
      status = USBH_OK;
    }
    else
    {
      USBH_ErrLog("Max Class Number reached");
      status = USBH_FAIL; 
    }
  }
  else
  {
    USBH_ErrLog("Invalid Class handle");
    status = USBH_FAIL; 
  }
  
  return status;
}