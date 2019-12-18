#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ MC0; } ;
struct TYPE_6__ {int /*<<< orphan*/  reg; TYPE_1__ bit; } ;
struct TYPE_7__ {TYPE_2__ INTFLAG; } ;
struct TYPE_8__ {TYPE_3__ COUNT16; } ;

/* Variables and functions */
 TYPE_4__* TC4 ; 
 int /*<<< orphan*/  TC_INTENCLR_MC0 ; 
 int /*<<< orphan*/  ms_clk ; 

void TC4_Handler() {
    if (TC4->COUNT16.INTFLAG.bit.MC0) {
        TC4->COUNT16.INTFLAG.reg = TC_INTENCLR_MC0;
        ms_clk++;
    }
}