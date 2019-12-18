#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_13__ {scalar_t__ RXNACK; } ;
struct TYPE_14__ {TYPE_5__ bit; } ;
struct TYPE_11__ {scalar_t__ MB; } ;
struct TYPE_12__ {TYPE_3__ bit; } ;
struct TYPE_9__ {int DATA; } ;
struct TYPE_10__ {TYPE_1__ bit; } ;
struct TYPE_15__ {TYPE_6__ STATUS; TYPE_4__ INTFLAG; TYPE_2__ DATA; } ;
struct TYPE_16__ {TYPE_7__ I2CM; } ;

/* Variables and functions */
 TYPE_8__* SERCOM0 ; 
 int /*<<< orphan*/  i2c0_start (int) ; 
 int /*<<< orphan*/  i2c0_stop () ; 

uint8_t i2c0_transmit(uint8_t address, uint8_t *data, uint16_t length, uint16_t timeout) {
    if (!length) return 0;

    i2c0_start(address);

    while (length) {
        SERCOM0->I2CM.DATA.bit.DATA = *data;
        while (SERCOM0->I2CM.INTFLAG.bit.MB == 0) {
        }
        while (SERCOM0->I2CM.STATUS.bit.RXNACK) {
        }

        data++;
        length--;
    }

    i2c0_stop();

    return 1;
}