#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ gState; TYPE_1__* pActiveClass; } ;
typedef  TYPE_2__ USBH_HandleTypeDef ;
struct TYPE_5__ {int /*<<< orphan*/  (* SOFProcess ) (TYPE_2__*) ;} ;

/* Variables and functions */
 scalar_t__ HOST_CLASS ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void  USBH_HandleSof  (USBH_HandleTypeDef *phost)
{
  if((phost->gState == HOST_CLASS)&&(phost->pActiveClass != NULL))
  {
    phost->pActiveClass->SOFProcess(phost);
  }
}