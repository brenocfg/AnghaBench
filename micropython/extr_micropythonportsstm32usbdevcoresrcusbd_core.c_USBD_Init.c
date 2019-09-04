#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  USBD_StatusTypeDef ;
struct TYPE_4__ {int /*<<< orphan*/  id; int /*<<< orphan*/  dev_state; int /*<<< orphan*/ * pDesc; int /*<<< orphan*/ * pClass; } ;
typedef  TYPE_1__ USBD_HandleTypeDef ;
typedef  int /*<<< orphan*/  USBD_DescriptorsTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_FAIL ; 
 int /*<<< orphan*/  USBD_LL_Init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_OK ; 
 int /*<<< orphan*/  USBD_STATE_DEFAULT ; 

USBD_StatusTypeDef USBD_Init(USBD_HandleTypeDef *pdev, USBD_DescriptorsTypeDef *pdesc, uint8_t id)
{
  /* Check whether the USB Host handle is valid */
  if(pdev == NULL)
  {
    return USBD_FAIL;
  }

  /* Unlink previous class*/
  if(pdev->pClass != NULL)
  {
    pdev->pClass = NULL;
  }

  /* Assign USBD Descriptors */
  if(pdesc != NULL)
  {
    pdev->pDesc = pdesc;
  }

  /* Set Device initial State */
  pdev->dev_state  = USBD_STATE_DEFAULT;
  pdev->id = id;
  /* Initialize low level driver */
  USBD_LL_Init(pdev, 0);

  return USBD_OK;
}