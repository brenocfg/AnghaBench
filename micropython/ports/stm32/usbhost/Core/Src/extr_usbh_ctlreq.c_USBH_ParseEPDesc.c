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
struct TYPE_3__ {void* bInterval; int /*<<< orphan*/  wMaxPacketSize; void* bmAttributes; void* bEndpointAddress; void* bDescriptorType; void* bLength; } ;
typedef  TYPE_1__ USBH_EpDescTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  LE16 (void**) ; 

__attribute__((used)) static void  USBH_ParseEPDesc (USBH_EpDescTypeDef  *ep_descriptor, 
                               uint8_t *buf)
{
  
  ep_descriptor->bLength          = *(uint8_t  *) (buf + 0);
  ep_descriptor->bDescriptorType  = *(uint8_t  *) (buf + 1);
  ep_descriptor->bEndpointAddress = *(uint8_t  *) (buf + 2);
  ep_descriptor->bmAttributes     = *(uint8_t  *) (buf + 3);
  ep_descriptor->wMaxPacketSize   = LE16 (buf + 4);
  ep_descriptor->bInterval        = *(uint8_t  *) (buf + 6);
}