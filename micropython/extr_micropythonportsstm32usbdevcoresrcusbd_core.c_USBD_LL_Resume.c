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
struct TYPE_3__ {int /*<<< orphan*/  dev_old_state; int /*<<< orphan*/  dev_state; } ;
typedef  TYPE_1__ USBD_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_OK ; 

USBD_StatusTypeDef USBD_LL_Resume(USBD_HandleTypeDef  *pdev)
{
  pdev->dev_state = pdev->dev_old_state;
  return USBD_OK;
}