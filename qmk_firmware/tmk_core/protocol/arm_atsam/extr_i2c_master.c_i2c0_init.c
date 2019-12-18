#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_27__ {scalar_t__ SYSOP; scalar_t__ ENABLE; } ;
struct TYPE_28__ {TYPE_8__ bit; } ;
struct TYPE_25__ {int MODE; int RUNSTDBY; int ENABLE; scalar_t__ SPEED; } ;
struct TYPE_26__ {TYPE_6__ bit; } ;
struct TYPE_24__ {TYPE_4__* PINCFG; TYPE_2__* PMUX; } ;
struct TYPE_22__ {int PMUXEN; } ;
struct TYPE_23__ {TYPE_3__ bit; } ;
struct TYPE_20__ {int PMUXE; int PMUXO; } ;
struct TYPE_21__ {TYPE_1__ bit; } ;
struct TYPE_19__ {TYPE_5__* Group; } ;
struct TYPE_15__ {int BUSSTATE; } ;
struct TYPE_16__ {TYPE_10__ bit; } ;
struct TYPE_17__ {TYPE_11__ STATUS; TYPE_9__ SYNCBUSY; TYPE_7__ CTRLA; } ;
struct TYPE_18__ {TYPE_12__ I2CM; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_SERCOM_I2C0 ; 
 int /*<<< orphan*/  CLK_set_i2c0_freq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBGC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_I2C0_INIT_BEGIN ; 
 int /*<<< orphan*/  DC_I2C0_INIT_COMPLETE ; 
 int /*<<< orphan*/  DC_I2C0_INIT_SYNC_ENABLING ; 
 int /*<<< orphan*/  DC_I2C0_INIT_SYNC_SYSOP ; 
 int /*<<< orphan*/  DC_I2C0_INIT_WAIT_IDLE ; 
 int /*<<< orphan*/  FREQ_I2C0_DEFAULT ; 
 TYPE_14__* PORT ; 
 TYPE_13__* SERCOM0 ; 

void i2c0_init(void) {
    DBGC(DC_I2C0_INIT_BEGIN);

    CLK_set_i2c0_freq(CHAN_SERCOM_I2C0, FREQ_I2C0_DEFAULT);

    // MCU
    PORT->Group[0].PMUX[4].bit.PMUXE    = 2;
    PORT->Group[0].PMUX[4].bit.PMUXO    = 2;
    PORT->Group[0].PINCFG[8].bit.PMUXEN = 1;
    PORT->Group[0].PINCFG[9].bit.PMUXEN = 1;

    // I2C
    // Note: SW Reset handled in CLK_set_i2c0_freq clks.c

    SERCOM0->I2CM.CTRLA.bit.MODE = 5;  // Set master mode

    SERCOM0->I2CM.CTRLA.bit.SPEED    = 0;  // Set to 1 for Fast-mode Plus (FM+) up to 1 MHz
    SERCOM0->I2CM.CTRLA.bit.RUNSTDBY = 1;  // Enabled

    SERCOM0->I2CM.CTRLA.bit.ENABLE = 1;  // Enable the device
    while (SERCOM0->I2CM.SYNCBUSY.bit.ENABLE) {
        DBGC(DC_I2C0_INIT_SYNC_ENABLING);
    }  // Wait for SYNCBUSY.ENABLE to clear

    SERCOM0->I2CM.STATUS.bit.BUSSTATE = 1;  // Force into IDLE state
    while (SERCOM0->I2CM.SYNCBUSY.bit.SYSOP) {
        DBGC(DC_I2C0_INIT_SYNC_SYSOP);
    }
    while (SERCOM0->I2CM.STATUS.bit.BUSSTATE != 1) {
        DBGC(DC_I2C0_INIT_WAIT_IDLE);
    }  // Wait while not idle

    DBGC(DC_I2C0_INIT_COMPLETE);
}