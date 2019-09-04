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
typedef  void* uint8_t ;
struct TYPE_3__ {void* iInterface; void* bInterfaceProtocol; void* bInterfaceSubClass; void* bInterfaceClass; void* bNumEndpoints; void* bAlternateSetting; void* bInterfaceNumber; void* bDescriptorType; void* bLength; } ;
typedef  TYPE_1__ USBH_InterfaceDescTypeDef ;

/* Variables and functions */

__attribute__((used)) static void  USBH_ParseInterfaceDesc (USBH_InterfaceDescTypeDef *if_descriptor, 
                                      uint8_t *buf)
{
  if_descriptor->bLength            = *(uint8_t  *) (buf + 0);
  if_descriptor->bDescriptorType    = *(uint8_t  *) (buf + 1);
  if_descriptor->bInterfaceNumber   = *(uint8_t  *) (buf + 2);
  if_descriptor->bAlternateSetting  = *(uint8_t  *) (buf + 3);
  if_descriptor->bNumEndpoints      = *(uint8_t  *) (buf + 4);
  if_descriptor->bInterfaceClass    = *(uint8_t  *) (buf + 5);
  if_descriptor->bInterfaceSubClass = *(uint8_t  *) (buf + 6);
  if_descriptor->bInterfaceProtocol = *(uint8_t  *) (buf + 7);
  if_descriptor->iInterface         = *(uint8_t  *) (buf + 8);
}