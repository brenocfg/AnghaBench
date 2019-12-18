#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_15__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_30__ {scalar_t__ ENABLE; } ;
struct TYPE_28__ {int DORD; int CPOL; int CPHA; int DIPO; int MODE; int ENABLE; scalar_t__ DOPO; } ;
struct TYPE_29__ {TYPE_7__ bit; } ;
struct TYPE_22__ {int reg; } ;
struct TYPE_27__ {TYPE_5__* PINCFG; TYPE_3__* PMUX; TYPE_1__ DIRSET; } ;
struct TYPE_25__ {int PMUXEN; } ;
struct TYPE_26__ {TYPE_4__ bit; } ;
struct TYPE_23__ {int /*<<< orphan*/  SR_EXP_SCLK_MUX_SEL; int /*<<< orphan*/  SR_EXP_DATAOUT_MUX_SEL; } ;
struct TYPE_24__ {TYPE_2__ bit; } ;
struct TYPE_21__ {TYPE_6__* Group; } ;
struct TYPE_16__ {TYPE_9__ bit; } ;
struct TYPE_17__ {TYPE_10__ SYNCBUSY; TYPE_8__ CTRLA; } ;
struct TYPE_20__ {TYPE_11__ SPI; } ;
struct TYPE_18__ {int E_UP_N; int S_DN1; int E_DN1_N; int SRC_1; int SRC_2; int IRST; scalar_t__ SDB_N; scalar_t__ E_VBUS_2; scalar_t__ E_VBUS_1; scalar_t__ S_UP; scalar_t__ HUB_RESET_N; scalar_t__ HUB_CONNECT; } ;
struct TYPE_19__ {TYPE_12__ bit; scalar_t__ reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_SERCOM_SPI ; 
 int /*<<< orphan*/  CLK_set_spi_freq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBGC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_SPI_INIT_BEGIN ; 
 int /*<<< orphan*/  DC_SPI_INIT_COMPLETE ; 
 int /*<<< orphan*/  DC_SPI_SYNC_ENABLING ; 
 int /*<<< orphan*/  FREQ_SPI_DEFAULT ; 
 TYPE_15__* PORT ; 
 int /*<<< orphan*/  SR_EXP_DATAOUT_MUX ; 
 int SR_EXP_DATAOUT_PIN ; 
 size_t SR_EXP_DATAOUT_PORT ; 
 int /*<<< orphan*/  SR_EXP_OE_N_DIS ; 
 int /*<<< orphan*/  SR_EXP_OE_N_ENA ; 
 int SR_EXP_OE_N_PIN ; 
 size_t SR_EXP_OE_N_PORT ; 
 int /*<<< orphan*/  SR_EXP_RCLK_HI ; 
 int SR_EXP_RCLK_PIN ; 
 size_t SR_EXP_RCLK_PORT ; 
 int /*<<< orphan*/  SR_EXP_SCLK_MUX ; 
 int SR_EXP_SCLK_PIN ; 
 size_t SR_EXP_SCLK_PORT ; 
 TYPE_14__* SR_EXP_SERCOM ; 
 int /*<<< orphan*/  SR_EXP_WriteData () ; 
 TYPE_13__ sr_exp_data ; 

void SR_EXP_Init(void) {
    DBGC(DC_SPI_INIT_BEGIN);

    CLK_set_spi_freq(CHAN_SERCOM_SPI, FREQ_SPI_DEFAULT);

    // Set up MCU Shift Register pins
    PORT->Group[SR_EXP_RCLK_PORT].DIRSET.reg = (1 << SR_EXP_RCLK_PIN);
    PORT->Group[SR_EXP_OE_N_PORT].DIRSET.reg = (1 << SR_EXP_OE_N_PIN);

    // Set up MCU SPI pins
    PORT->Group[SR_EXP_DATAOUT_PORT].PMUX[SR_EXP_DATAOUT_PIN / 2].bit.SR_EXP_DATAOUT_MUX_SEL = SR_EXP_DATAOUT_MUX;  // MUX select for sercom
    PORT->Group[SR_EXP_SCLK_PORT].PMUX[SR_EXP_SCLK_PIN / 2].bit.SR_EXP_SCLK_MUX_SEL          = SR_EXP_SCLK_MUX;     // MUX select for sercom
    PORT->Group[SR_EXP_DATAOUT_PORT].PINCFG[SR_EXP_DATAOUT_PIN].bit.PMUXEN                   = 1;                   // MUX Enable
    PORT->Group[SR_EXP_SCLK_PORT].PINCFG[SR_EXP_SCLK_PIN].bit.PMUXEN                         = 1;                   // MUX Enable

    // Initialize Shift Register
    SR_EXP_OE_N_DIS;
    SR_EXP_RCLK_HI;

    SR_EXP_SERCOM->SPI.CTRLA.bit.DORD = 1;  // Data Order - LSB is transferred first
    SR_EXP_SERCOM->SPI.CTRLA.bit.CPOL = 1;  // Clock Polarity - SCK high when idle. Leading edge of cycle is falling. Trailing rising.
    SR_EXP_SERCOM->SPI.CTRLA.bit.CPHA = 1;  // Clock Phase - Leading Edge Falling, change, Trailing Edge - Rising, sample
    SR_EXP_SERCOM->SPI.CTRLA.bit.DIPO = 3;  // Data In Pinout - SERCOM PAD[3] is used as data input (Configure away from DOPO. Not using input.)
    SR_EXP_SERCOM->SPI.CTRLA.bit.DOPO = 0;  // Data Output PAD[0], Serial Clock PAD[1]
    SR_EXP_SERCOM->SPI.CTRLA.bit.MODE = 3;  // Operating Mode - Master operation

    SR_EXP_SERCOM->SPI.CTRLA.bit.ENABLE = 1;  // Enable - Peripheral is enabled or being enabled
    while (SR_EXP_SERCOM->SPI.SYNCBUSY.bit.ENABLE) {
        DBGC(DC_SPI_SYNC_ENABLING);
    }

    sr_exp_data.reg             = 0;
    sr_exp_data.bit.HUB_CONNECT = 0;
    sr_exp_data.bit.HUB_RESET_N = 0;
    sr_exp_data.bit.S_UP        = 0;
    sr_exp_data.bit.E_UP_N      = 1;
    sr_exp_data.bit.S_DN1       = 1;
    sr_exp_data.bit.E_DN1_N     = 1;
    sr_exp_data.bit.E_VBUS_1    = 0;
    sr_exp_data.bit.E_VBUS_2    = 0;
    sr_exp_data.bit.SRC_1       = 1;
    sr_exp_data.bit.SRC_2       = 1;
    sr_exp_data.bit.IRST        = 1;
    sr_exp_data.bit.SDB_N       = 0;
    SR_EXP_WriteData();

    // Enable Shift Register output
    SR_EXP_OE_N_ENA;

    DBGC(DC_SPI_INIT_COMPLETE);
}