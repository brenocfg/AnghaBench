#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USBH_StatusTypeDef ;
struct TYPE_12__ {TYPE_1__* pActiveClass; } ;
typedef  TYPE_5__ USBH_HandleTypeDef ;
struct TYPE_9__ {int /*<<< orphan*/  Tag; int /*<<< orphan*/  Signature; } ;
struct TYPE_10__ {TYPE_2__ field; } ;
struct TYPE_11__ {int /*<<< orphan*/  cmd_state; int /*<<< orphan*/  state; TYPE_3__ cbw; } ;
struct TYPE_13__ {TYPE_4__ hbot; } ;
struct TYPE_8__ {TYPE_6__* pData; } ;
typedef  TYPE_6__ MSC_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  BOT_CBW_SIGNATURE ; 
 int /*<<< orphan*/  BOT_CBW_TAG ; 
 int /*<<< orphan*/  BOT_CMD_SEND ; 
 int /*<<< orphan*/  BOT_SEND_CBW ; 
 int /*<<< orphan*/  USBH_OK ; 

USBH_StatusTypeDef USBH_MSC_BOT_Init(USBH_HandleTypeDef *phost)
{
  
  MSC_HandleTypeDef *MSC_Handle =  phost->pActiveClass->pData;
  
  MSC_Handle->hbot.cbw.field.Signature = BOT_CBW_SIGNATURE;
  MSC_Handle->hbot.cbw.field.Tag = BOT_CBW_TAG;
  MSC_Handle->hbot.state = BOT_SEND_CBW;    
  MSC_Handle->hbot.cmd_state = BOT_CMD_SEND;   
  
  return USBH_OK;
}