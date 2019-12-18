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
struct TYPE_5__ {scalar_t__ ERROR; } ;
struct TYPE_6__ {int /*<<< orphan*/  reg; TYPE_1__ bit; } ;
struct TYPE_7__ {TYPE_2__ INTFLAG; } ;
struct TYPE_8__ {TYPE_3__ I2CM; } ;

/* Variables and functions */
 TYPE_4__* SERCOM1 ; 
 int /*<<< orphan*/  SERCOM_I2CM_INTENCLR_ERROR ; 

void SERCOM1_0_Handler(void) {
    if (SERCOM1->I2CM.INTFLAG.bit.ERROR) {
        SERCOM1->I2CM.INTFLAG.reg = SERCOM_I2CM_INTENCLR_ERROR;
    }
}