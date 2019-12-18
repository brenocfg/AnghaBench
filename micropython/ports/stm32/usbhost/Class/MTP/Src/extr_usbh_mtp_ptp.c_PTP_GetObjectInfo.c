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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_14__ {TYPE_1__* pActiveClass; } ;
typedef  TYPE_5__ USBH_HandleTypeDef ;
struct TYPE_11__ {scalar_t__* data; } ;
struct TYPE_12__ {TYPE_2__ payload; } ;
struct TYPE_13__ {TYPE_3__ data_container; } ;
struct TYPE_16__ {TYPE_4__ ptp; } ;
struct TYPE_15__ {int /*<<< orphan*/  Filename; void* SequenceNumber; void* AssociationDesc; void* AssociationType; void* ParentObject; void* ImageBitDepth; void* ImagePixHeight; void* ImagePixWidth; void* ThumbPixHeight; void* ThumbPixWidth; void* ThumbCompressedSize; void* ThumbFormat; void* ObjectCompressedSize; void* ProtectionStatus; void* ObjectFormat; void* StorageID; } ;
struct TYPE_10__ {TYPE_7__* pData; } ;
typedef  TYPE_6__ PTP_ObjectInfoTypedef ;
typedef  TYPE_7__ MTP_HandleTypeDef ;

/* Variables and functions */
 void* LE16 (scalar_t__*) ; 
 void* LE32 (scalar_t__*) ; 
 int /*<<< orphan*/  PTP_GetString (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 size_t PTP_oi_AssociationDesc ; 
 size_t PTP_oi_AssociationType ; 
 size_t PTP_oi_ImageBitDepth ; 
 size_t PTP_oi_ImagePixHeight ; 
 size_t PTP_oi_ImagePixWidth ; 
 size_t PTP_oi_ObjectCompressedSize ; 
 size_t PTP_oi_ObjectFormat ; 
 size_t PTP_oi_ParentObject ; 
 size_t PTP_oi_ProtectionStatus ; 
 size_t PTP_oi_SequenceNumber ; 
 size_t PTP_oi_StorageID ; 
 size_t PTP_oi_ThumbCompressedSize ; 
 size_t PTP_oi_ThumbFormat ; 
 size_t PTP_oi_ThumbPixHeight ; 
 size_t PTP_oi_ThumbPixWidth ; 
 size_t PTP_oi_filenamelen ; 

__attribute__((used)) static void PTP_GetObjectInfo (USBH_HandleTypeDef *phost, PTP_ObjectInfoTypedef *object_info)
{
  MTP_HandleTypeDef    *MTP_Handle =  phost->pActiveClass->pData;   
  uint8_t *data = MTP_Handle->ptp.data_container.payload.data;
  uint16_t filenamelen;
  
  object_info->StorageID=LE32(&data[PTP_oi_StorageID]);
  object_info->ObjectFormat=LE16(&data[PTP_oi_ObjectFormat]);
  object_info->ProtectionStatus=LE16(&data[PTP_oi_ProtectionStatus]);
  object_info->ObjectCompressedSize=LE32(&data[PTP_oi_ObjectCompressedSize]);
  
  /* For Samsung Galaxy */
  if ((data[PTP_oi_filenamelen] == 0) && (data[PTP_oi_filenamelen+4] != 0)) 
  {
    data += 4;
  }
  object_info->ThumbFormat=LE16(&data[PTP_oi_ThumbFormat]);
  object_info->ThumbCompressedSize=LE32(&data[PTP_oi_ThumbCompressedSize]);
  object_info->ThumbPixWidth=LE32(&data[PTP_oi_ThumbPixWidth]);
  object_info->ThumbPixHeight=LE32(&data[PTP_oi_ThumbPixHeight]);
  object_info->ImagePixWidth=LE32(&data[PTP_oi_ImagePixWidth]);
  object_info->ImagePixHeight=LE32(&data[PTP_oi_ImagePixHeight]);
  object_info->ImageBitDepth=LE32(&data[PTP_oi_ImageBitDepth]);
  object_info->ParentObject=LE32(&data[PTP_oi_ParentObject]);
  object_info->AssociationType=LE16(&data[PTP_oi_AssociationType]);
  object_info->AssociationDesc=LE32(&data[PTP_oi_AssociationDesc]);
  object_info->SequenceNumber=LE32(&data[PTP_oi_SequenceNumber]);
  PTP_GetString(object_info->Filename, &data[PTP_oi_filenamelen], &filenamelen);
}