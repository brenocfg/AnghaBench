#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ SYSOP; } ;
struct TYPE_10__ {TYPE_3__ bit; } ;
struct TYPE_7__ {int CMD; } ;
struct TYPE_8__ {TYPE_1__ bit; } ;
struct TYPE_11__ {TYPE_4__ SYNCBUSY; TYPE_2__ CTRLB; } ;
struct TYPE_12__ {TYPE_5__ I2CM; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_USB_WRITE2422_BLOCK_BEGIN ; 
 int /*<<< orphan*/  DC_USB_WRITE2422_BLOCK_COMPLETE ; 
 int /*<<< orphan*/  DC_USB_WRITE2422_BLOCK_SYNC_SYSOP ; 
 TYPE_6__* SERCOM0 ; 
 int /*<<< orphan*/  USB2422_ADDR ; 
 int /*<<< orphan*/  USB2422_shadow ; 
 unsigned char* i2c0_buf ; 
 int /*<<< orphan*/  i2c0_transmit (int /*<<< orphan*/ ,unsigned char*,int,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  wait_us (int) ; 

void USB_write2422_block(void) {
    unsigned char *dest = i2c0_buf;
    unsigned char *src;
    unsigned char *base = (unsigned char *)&USB2422_shadow;

    DBGC(DC_USB_WRITE2422_BLOCK_BEGIN);

    for (src = base; src < base + 256; src += 32) {
        dest[0] = src - base;
        dest[1] = 32;
        memcpy(&dest[2], src, 32);
        i2c0_transmit(USB2422_ADDR, dest, 34, 50000);
        SERCOM0->I2CM.CTRLB.bit.CMD = 0x03;
        while (SERCOM0->I2CM.SYNCBUSY.bit.SYSOP) {
            DBGC(DC_USB_WRITE2422_BLOCK_SYNC_SYSOP);
        }
        wait_us(100);
    }

    DBGC(DC_USB_WRITE2422_BLOCK_COMPLETE);
}