#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_20__ {int /*<<< orphan*/  reg; } ;
struct TYPE_18__ {int /*<<< orphan*/  RESRDY; } ;
struct TYPE_19__ {TYPE_7__ bit; } ;
struct TYPE_16__ {scalar_t__ SWTRIG; scalar_t__ INPUTCTRL; } ;
struct TYPE_17__ {TYPE_5__ bit; } ;
struct TYPE_14__ {int START; } ;
struct TYPE_15__ {TYPE_3__ bit; } ;
struct TYPE_12__ {int /*<<< orphan*/  MUXPOS; } ;
struct TYPE_13__ {TYPE_1__ bit; } ;
struct TYPE_11__ {TYPE_9__ RESULT; TYPE_8__ INTFLAG; TYPE_6__ SYNCBUSY; TYPE_4__ SWTRIG; TYPE_2__ INPUTCTRL; } ;

/* Variables and functions */
 TYPE_10__* ADC0 ; 

uint16_t adc_get(uint8_t muxpos) {
    ADC0->INPUTCTRL.bit.MUXPOS = muxpos;
    while (ADC0->SYNCBUSY.bit.INPUTCTRL) {
    }

    ADC0->SWTRIG.bit.START = 1;
    while (ADC0->SYNCBUSY.bit.SWTRIG) {
    }
    while (!ADC0->INTFLAG.bit.RESRDY) {
    }

    return ADC0->RESULT.reg;
}