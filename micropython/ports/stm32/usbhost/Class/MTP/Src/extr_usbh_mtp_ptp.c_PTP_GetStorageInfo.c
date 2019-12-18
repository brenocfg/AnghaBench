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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct TYPE_14__ {TYPE_1__* pActiveClass; } ;
typedef  TYPE_5__ USBH_HandleTypeDef ;
struct TYPE_11__ {int /*<<< orphan*/ * data; } ;
struct TYPE_12__ {TYPE_2__ payload; } ;
struct TYPE_13__ {TYPE_3__ data_container; } ;
struct TYPE_16__ {TYPE_4__ ptp; } ;
struct TYPE_15__ {int /*<<< orphan*/  VolumeLabel; int /*<<< orphan*/  StorageDescription; int /*<<< orphan*/  FreeSpaceInImages; void* FreeSpaceInBytes; void* MaxCapability; void* AccessCapability; void* FilesystemType; void* StorageType; } ;
struct TYPE_10__ {TYPE_7__* pData; } ;
typedef  TYPE_6__ PTP_StorageInfoTypedef ;
typedef  TYPE_7__ MTP_HandleTypeDef ;

/* Variables and functions */
 void* LE16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LE32 (int /*<<< orphan*/ *) ; 
 void* LE64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PTP_GetString (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 size_t PTP_si_AccessCapability ; 
 size_t PTP_si_FilesystemType ; 
 size_t PTP_si_FreeSpaceInBytes ; 
 size_t PTP_si_FreeSpaceInImages ; 
 size_t PTP_si_MaxCapability ; 
 size_t PTP_si_StorageDescription ; 
 size_t PTP_si_StorageType ; 

__attribute__((used)) static void PTP_GetStorageInfo (USBH_HandleTypeDef *phost, uint32_t storage_id, PTP_StorageInfoTypedef *stor_info)
{
  MTP_HandleTypeDef    *MTP_Handle =  phost->pActiveClass->pData;   
  uint8_t *data = MTP_Handle->ptp.data_container.payload.data;

  uint16_t len;
  
  stor_info->StorageType=LE16(&data[PTP_si_StorageType]);
  stor_info->FilesystemType=LE16(&data[PTP_si_FilesystemType]);
  stor_info->AccessCapability=LE16(&data[PTP_si_AccessCapability]);
  stor_info->MaxCapability=LE64(&data[PTP_si_MaxCapability]);
  stor_info->FreeSpaceInBytes=LE64(&data[PTP_si_FreeSpaceInBytes]);
  stor_info->FreeSpaceInImages=LE32(&data[PTP_si_FreeSpaceInImages]);
  
  PTP_GetString(stor_info->StorageDescription, &data[PTP_si_StorageDescription], &len);
  PTP_GetString(stor_info->VolumeLabel, &data[PTP_si_StorageDescription+len*2+1], &len);   
}