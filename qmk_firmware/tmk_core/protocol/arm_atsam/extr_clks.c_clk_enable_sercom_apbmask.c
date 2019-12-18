#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int SERCOM2_; int SERCOM3_; } ;
struct TYPE_10__ {TYPE_3__ bit; } ;
struct TYPE_7__ {int SERCOM0_; int SERCOM1_; } ;
struct TYPE_8__ {TYPE_1__ bit; } ;
struct TYPE_11__ {TYPE_4__ APBBMASK; TYPE_2__ APBAMASK; } ;
typedef  TYPE_5__ Mclk ;

/* Variables and functions */
 TYPE_5__* MCLK ; 

void clk_enable_sercom_apbmask(int sercomn) {
    Mclk *pmclk = MCLK;
    switch (sercomn) {
        case 0:
            pmclk->APBAMASK.bit.SERCOM0_ = 1;
            break;
        case 1:
            pmclk->APBAMASK.bit.SERCOM1_ = 1;
            break;
        case 2:
            pmclk->APBBMASK.bit.SERCOM2_ = 1;
            break;
        case 3:
            pmclk->APBBMASK.bit.SERCOM3_ = 1;
            break;
        default:
            break;
    }
}