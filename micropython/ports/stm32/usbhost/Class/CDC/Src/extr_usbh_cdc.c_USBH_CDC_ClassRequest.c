#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ USBH_StatusTypeDef ;
struct TYPE_8__ {int /*<<< orphan*/  (* pUser ) (TYPE_2__*,int /*<<< orphan*/ ) ;TYPE_1__* pActiveClass; } ;
typedef  TYPE_2__ USBH_HandleTypeDef ;
struct TYPE_9__ {int /*<<< orphan*/  LineCoding; } ;
struct TYPE_7__ {TYPE_3__* pData; } ;
typedef  TYPE_3__ CDC_HandleTypeDef ;

/* Variables and functions */
 scalar_t__ GetLineCoding (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HOST_USER_CLASS_ACTIVE ; 
 scalar_t__ USBH_FAIL ; 
 scalar_t__ USBH_OK ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static USBH_StatusTypeDef USBH_CDC_ClassRequest (USBH_HandleTypeDef *phost)
{   
  USBH_StatusTypeDef status = USBH_FAIL ;  
  CDC_HandleTypeDef *CDC_Handle =  phost->pActiveClass->pData;  
  
  /*Issue the get line coding request*/
  status =   GetLineCoding(phost, &CDC_Handle->LineCoding);
  if(status == USBH_OK)
  {
    phost->pUser(phost, HOST_USER_CLASS_ACTIVE); 
  }
  return status;
}