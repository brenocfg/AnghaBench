#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_14__ {TYPE_1__* pActiveClass; } ;
typedef  TYPE_5__ USBH_HandleTypeDef ;
struct TYPE_11__ {int /*<<< orphan*/ * data; } ;
struct TYPE_12__ {TYPE_2__ payload; } ;
struct TYPE_13__ {TYPE_3__ data_container; } ;
struct TYPE_16__ {TYPE_4__ ptp; } ;
struct TYPE_15__ {int /*<<< orphan*/  Storage; int /*<<< orphan*/  n; } ;
struct TYPE_10__ {TYPE_7__* pData; } ;
typedef  TYPE_6__ PTP_StorageIDsTypedef ;
typedef  TYPE_7__ MTP_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  PTP_GetArray32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void PTP_GetStorageIDs (USBH_HandleTypeDef *phost, PTP_StorageIDsTypedef *stor_ids)
{
  MTP_HandleTypeDef    *MTP_Handle =  phost->pActiveClass->pData;   
  uint8_t *data = MTP_Handle->ptp.data_container.payload.data;

  stor_ids->n = PTP_GetArray32 (stor_ids->Storage, data, 0); 
}