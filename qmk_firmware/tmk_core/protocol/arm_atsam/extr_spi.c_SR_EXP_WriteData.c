#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  TXC; int /*<<< orphan*/  DRE; } ;
struct TYPE_9__ {TYPE_1__ bit; } ;
struct TYPE_10__ {int DATA; } ;
struct TYPE_11__ {TYPE_3__ bit; } ;
struct TYPE_12__ {TYPE_2__ INTFLAG; TYPE_4__ DATA; } ;
struct TYPE_14__ {TYPE_5__ SPI; } ;
struct TYPE_13__ {int reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_SPI_WRITE_DRE ; 
 int /*<<< orphan*/  DC_SPI_WRITE_TXC_1 ; 
 int /*<<< orphan*/  DC_SPI_WRITE_TXC_2 ; 
 int /*<<< orphan*/  SR_EXP_RCLK_HI ; 
 int /*<<< orphan*/  SR_EXP_RCLK_LO ; 
 TYPE_7__* SR_EXP_SERCOM ; 
 TYPE_6__ sr_exp_data ; 

void SR_EXP_WriteData(void) {
    SR_EXP_RCLK_LO;

    while (!(SR_EXP_SERCOM->SPI.INTFLAG.bit.DRE)) {
        DBGC(DC_SPI_WRITE_DRE);
    }

    SR_EXP_SERCOM->SPI.DATA.bit.DATA = sr_exp_data.reg & 0xFF;  // Shift in bits 7-0
    while (!(SR_EXP_SERCOM->SPI.INTFLAG.bit.TXC)) {
        DBGC(DC_SPI_WRITE_TXC_1);
    }

    SR_EXP_SERCOM->SPI.DATA.bit.DATA = (sr_exp_data.reg >> 8) & 0xFF;  // Shift in bits 15-8
    while (!(SR_EXP_SERCOM->SPI.INTFLAG.bit.TXC)) {
        DBGC(DC_SPI_WRITE_TXC_2);
    }

    SR_EXP_RCLK_HI;
}