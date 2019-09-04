#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {TYPE_1__* pActiveClass; } ;
typedef  TYPE_2__ USBH_HandleTypeDef ;
struct TYPE_7__ {int /*<<< orphan*/  is_ready; } ;
struct TYPE_5__ {TYPE_3__* pData; } ;
typedef  TYPE_3__ MTP_HandleTypeDef ;

/* Variables and functions */

uint8_t USBH_MTP_IsReady (USBH_HandleTypeDef *phost)
{
  MTP_HandleTypeDef *MTP_Handle =  phost->pActiveClass->pData;
  
  return (MTP_Handle->is_ready);
}