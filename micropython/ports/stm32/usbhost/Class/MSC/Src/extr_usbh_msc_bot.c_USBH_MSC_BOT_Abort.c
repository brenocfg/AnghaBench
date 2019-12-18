#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_7__ {TYPE_1__* pActiveClass; } ;
typedef  TYPE_2__ USBH_HandleTypeDef ;
struct TYPE_8__ {int /*<<< orphan*/  OutEp; int /*<<< orphan*/  InEp; } ;
struct TYPE_6__ {TYPE_3__* pData; } ;
typedef  TYPE_3__ MSC_HandleTypeDef ;

/* Variables and functions */
#define  BOT_DIR_IN 129 
#define  BOT_DIR_OUT 128 
 int /*<<< orphan*/  USBH_ClrFeature (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBH_FAIL ; 

__attribute__((used)) static USBH_StatusTypeDef USBH_MSC_BOT_Abort(USBH_HandleTypeDef *phost, uint8_t lun, uint8_t dir)
{
  USBH_StatusTypeDef status = USBH_FAIL;
  MSC_HandleTypeDef *MSC_Handle =  phost->pActiveClass->pData;
  
  switch (dir)
  {
  case BOT_DIR_IN :
    /* send ClrFeture on Bulk IN endpoint */
    status = USBH_ClrFeature(phost, MSC_Handle->InEp);
    
    break;
    
  case BOT_DIR_OUT :
    /*send ClrFeature on Bulk OUT endpoint */
    status = USBH_ClrFeature(phost, MSC_Handle->OutEp);
    break;
    
  default:
    break;
  }
  return status;
}