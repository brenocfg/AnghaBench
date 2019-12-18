#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  unsigned int uint32_t ;
typedef  unsigned int uint16_t ;
typedef  unsigned int USBx_DFIFO ;
struct TYPE_2__ {int DIEPTSIZ; int DIEPCTL; } ;

/* Variables and functions */
 unsigned int MAX_RESP_LEN ; 
 int USB_OTG_DIEPCTL_CNAK ; 
 int USB_OTG_DIEPCTL_EPENA ; 
 int USB_OTG_DIEPTSIZ_PKTCNT ; 
 unsigned int USB_OTG_DIEPTSIZ_XFRSIZ ; 
 TYPE_1__* USBx_INEP (unsigned int) ; 
 int /*<<< orphan*/  hexdump (void const*,unsigned int) ; 
 int /*<<< orphan*/  puts (char*) ; 

void USB_WritePacket(const void *src, uint16_t len, uint32_t ep) {
  #ifdef DEBUG_USB
  puts("writing ");
  hexdump(src, len);
  #endif

  uint8_t numpacket = (len + (MAX_RESP_LEN - 1U)) / MAX_RESP_LEN;
  uint32_t count32b = 0;
  count32b = (len + 3U) / 4U;

  // TODO: revisit this
  USBx_INEP(ep)->DIEPTSIZ = ((numpacket << 19) & USB_OTG_DIEPTSIZ_PKTCNT) |
                            (len               & USB_OTG_DIEPTSIZ_XFRSIZ);
  USBx_INEP(ep)->DIEPCTL |= (USB_OTG_DIEPCTL_CNAK | USB_OTG_DIEPCTL_EPENA);

  // load the FIFO
  const uint32_t *src_copy = (const uint32_t *)src;
  for (uint32_t i = 0; i < count32b; i++) {
    USBx_DFIFO(ep) = *src_copy;
    src_copy++;
  }
}