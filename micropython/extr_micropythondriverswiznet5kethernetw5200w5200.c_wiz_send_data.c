#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 scalar_t__ SBASE (int /*<<< orphan*/ ) ; 
 scalar_t__ SMASK ; 
 scalar_t__ SSIZE ; 
 int /*<<< orphan*/  WIZCHIP_WRITE_BUF (scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ getSn_TX_WR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setSn_TX_WR (int /*<<< orphan*/ ,scalar_t__) ; 

void wiz_send_data(uint8_t sn, uint8_t *wizdata, uint16_t len) {
    if (len == 0) {
        return;
    }

    uint16_t ptr = getSn_TX_WR(sn);
    uint16_t offset = ptr & SMASK;
    uint32_t addr = offset + SBASE(sn);

    if (offset + len > SSIZE) {
        // implement wrap-around circular buffer
        uint16_t size = SSIZE - offset;
        WIZCHIP_WRITE_BUF(addr, wizdata, size);
        WIZCHIP_WRITE_BUF(SBASE(sn), wizdata + size, len - size);
    } else {
        WIZCHIP_WRITE_BUF(addr, wizdata, len);
    }

    ptr += len;
    setSn_TX_WR(sn, ptr);
}