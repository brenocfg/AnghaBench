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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 scalar_t__ RBASE (int /*<<< orphan*/ ) ; 
 scalar_t__ RMASK ; 
 scalar_t__ RSIZE ; 
 int /*<<< orphan*/  WIZCHIP_READ_BUF (scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ getSn_RX_RD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setSn_RX_RD (int /*<<< orphan*/ ,scalar_t__) ; 

void wiz_recv_data(uint8_t sn, uint8_t *wizdata, uint16_t len) {
    if (len == 0) {
        return;
    }

    uint16_t ptr = getSn_RX_RD(sn);
    uint16_t offset = ptr & RMASK;
    uint16_t addr = RBASE(sn) + offset;

    if (offset + len > RSIZE) {
        // implement wrap-around circular buffer
        uint16_t size = RSIZE - offset;
        WIZCHIP_READ_BUF(addr, wizdata, size);
        WIZCHIP_READ_BUF(RBASE(sn), wizdata + size, len - size);
    } else {
        WIZCHIP_READ_BUF(addr, wizdata, len);
    }

    ptr += len;
    setSn_RX_RD(sn, ptr);
}