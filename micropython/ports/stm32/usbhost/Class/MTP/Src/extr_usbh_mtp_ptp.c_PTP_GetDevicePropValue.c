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
typedef  void* uint8_t ;
typedef  size_t uint32_t ;
typedef  int uint16_t ;
struct TYPE_14__ {TYPE_1__* pActiveClass; } ;
typedef  TYPE_5__ USBH_HandleTypeDef ;
struct TYPE_11__ {void** data; } ;
struct TYPE_12__ {TYPE_2__ payload; } ;
struct TYPE_13__ {TYPE_3__ data_container; } ;
struct TYPE_16__ {TYPE_4__ ptp; } ;
struct TYPE_15__ {scalar_t__ str; void* u64; void* i64; void* u32; void* i32; void* u16; void* i16; void* u8; void* i8; } ;
struct TYPE_10__ {TYPE_7__* pData; } ;
typedef  TYPE_6__ PTP_PropertyValueTypedef ;
typedef  TYPE_7__ MTP_HandleTypeDef ;

/* Variables and functions */
 void* LE16 (void**) ; 
 void* LE32 (void**) ; 
 void* LE64 (void**) ; 
#define  PTP_DTC_INT128 138 
#define  PTP_DTC_INT16 137 
#define  PTP_DTC_INT32 136 
#define  PTP_DTC_INT64 135 
#define  PTP_DTC_INT8 134 
#define  PTP_DTC_STR 133 
#define  PTP_DTC_UINT128 132 
#define  PTP_DTC_UINT16 131 
#define  PTP_DTC_UINT32 130 
#define  PTP_DTC_UINT64 129 
#define  PTP_DTC_UINT8 128 
 int /*<<< orphan*/  PTP_GetString (void**,void**,int*) ; 

__attribute__((used)) static void PTP_GetDevicePropValue(USBH_HandleTypeDef *phost, 
                                   uint32_t *offset, 
                                   uint32_t total, 
                                   PTP_PropertyValueTypedef* value, 
                                   uint16_t datatype)
{
  MTP_HandleTypeDef    *MTP_Handle =  phost->pActiveClass->pData;   
  uint8_t *data = MTP_Handle->ptp.data_container.payload.data;
  uint16_t len;
  switch (datatype) 
  {
  case PTP_DTC_INT8:
    value->i8 = *(uint8_t *)&(data[*offset]);
    *offset += 1;
    break;
  case PTP_DTC_UINT8:
    value->u8 = *(uint8_t *)&(data[*offset]);
    *offset += 1;                
    break;
  case PTP_DTC_INT16:
    
    value->i16 = LE16(&(data[*offset]));
    *offset += 2;                
    break;
  case PTP_DTC_UINT16:
    value->u16 = LE16(&(data[*offset]));                
    *offset += 2;                
    break;
  case PTP_DTC_INT32:
    value->i32 = LE32(&(data[*offset]));              
    *offset += 4;                
    break;
  case PTP_DTC_UINT32:
    value->u32 = LE32(&(data[*offset]));             
    *offset += 4;                
    break;
  case PTP_DTC_INT64:
    value->i64 = LE64(&(data[*offset]));            
    *offset += 8;                
    break;
  case PTP_DTC_UINT64:
    value->u64 = LE64(&(data[*offset]));              
    *offset += 8;                
    break;
    
  case PTP_DTC_UINT128:
    *offset += 16;
    break;
  case PTP_DTC_INT128:
    *offset += 16;
    break;
 
  case PTP_DTC_STR:
    
    PTP_GetString((uint8_t *)value->str, (uint8_t *)&(data[*offset]), &len);
    *offset += len*2+1;
    break;
  default:
    break;
  }
}