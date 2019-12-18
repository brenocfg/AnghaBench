#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_15__ {TYPE_1__* pActiveClass; } ;
typedef  TYPE_5__ USBH_HandleTypeDef ;
struct TYPE_12__ {int /*<<< orphan*/ * data; } ;
struct TYPE_13__ {TYPE_2__ payload; } ;
struct TYPE_14__ {TYPE_3__ data_container; } ;
struct TYPE_17__ {TYPE_4__ ptp; } ;
struct TYPE_16__ {void* datatype; int /*<<< orphan*/  propval; void* property; void* ObjectHandle; } ;
struct TYPE_11__ {TYPE_7__* pData; } ;
typedef  TYPE_6__ MTP_PropertiesTypedef ;
typedef  TYPE_7__ MTP_HandleTypeDef ;

/* Variables and functions */
 void* LE16 (int /*<<< orphan*/ *) ; 
 void* LE32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PTP_GetDevicePropValue (TYPE_5__*,scalar_t__*,scalar_t__,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static uint32_t PTP_GetObjectPropList (USBH_HandleTypeDef *phost, 
                                   MTP_PropertiesTypedef *props, 
                                   uint32_t len)
{ 
  MTP_HandleTypeDef    *MTP_Handle =  phost->pActiveClass->pData;   
  uint8_t *data = MTP_Handle->ptp.data_container.payload.data;
  uint32_t prop_count;
  uint32_t offset = 0, i;
  
 prop_count = LE32(data);

 
 if (prop_count == 0) 
 {
   return 0;
 }

 data += sizeof(uint32_t);
 len -= sizeof(uint32_t);
 
 for (i = 0; i < prop_count; i++) 
 {
   if (len <= 0) 
   {
     return 0;
   }
   
   props[i].ObjectHandle = LE32(data);
   data += sizeof(uint32_t);
   len -= sizeof(uint32_t);
   
   props[i].property = LE16(data);
   data += sizeof(uint16_t);
   len -= sizeof(uint16_t);
   
   props[i].datatype = LE16(data);
   data += sizeof(uint16_t);
   len -= sizeof(uint16_t);
   
   offset = 0;
   
   PTP_GetDevicePropValue(phost, &offset, len, &props[i].propval, props[i].datatype);
   
   data += offset;
   len -= offset;
 }
 
 return prop_count;
}