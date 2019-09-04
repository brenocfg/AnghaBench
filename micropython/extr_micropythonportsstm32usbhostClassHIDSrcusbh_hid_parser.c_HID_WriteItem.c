#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int* data; int shift; int physical_min; int physical_max; scalar_t__ count; int size; int resolution; } ;
typedef  TYPE_1__ HID_Report_ItemTypedef ;

/* Variables and functions */

uint32_t HID_WriteItem(HID_Report_ItemTypedef *ri, uint32_t value, uint8_t ndx)
{
  uint32_t x;
  uint32_t mask;
  uint32_t bofs;
  uint8_t *data=ri->data;
  uint8_t shift=ri->shift;
  
  if (value < ri->physical_min || value > ri->physical_max)  
  {
    return(1);
  }
  
    /* if this is an array, wee may need to offset ri->data.*/
  if (ri->count > 0)
  { 
    /* If app tries to read outside of the array. */
    if (ri->count >= ndx)
    {
      return(0);
    }
    /* calculate bit offset */
    bofs = ndx*ri->size;
    bofs += shift;
    /* calculate byte offset + shift pair from bit offset. */    
    data+=bofs/8;
    shift=(uint8_t)(bofs%8);

  }

  /* Convert physical value to logical value. */  
  if (ri->resolution != 1)
  {
    value=value/ri->resolution;
  }

  /* Write logical value to report in little endian order. */
  mask=(uint32_t)((1<<ri->size)-1);
  value = (value & mask) << shift;
  
  for(x=0; x < ((ri->size & 0x7) ? (ri->size/8)+1 : (ri->size/8)); x++)
  {
    *(ri->data+x)=(uint8_t)((*(ri->data+x) & ~(mask>>(x*8))) | ((value>>(x*8)) & (mask>>(x*8))));
  }
  return(0);
}