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
typedef  int /*<<< orphan*/  USBD_StatusTypeDef ;
struct TYPE_3__ {int /*<<< orphan*/  const* pClass; } ;
typedef  TYPE_1__ USBD_HandleTypeDef ;
typedef  int /*<<< orphan*/  USBD_ClassTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_FAIL ; 
 int /*<<< orphan*/  USBD_OK ; 

USBD_StatusTypeDef  USBD_RegisterClass(USBD_HandleTypeDef *pdev, const USBD_ClassTypeDef *pclass)
{
  USBD_StatusTypeDef   status = USBD_OK;
  if(pclass != 0)
  {
    /* link the class tgo the USB Device handle */
    pdev->pClass = pclass;
    status = USBD_OK;
  }
  else
  {
    status = USBD_FAIL;
  }

  return status;
}