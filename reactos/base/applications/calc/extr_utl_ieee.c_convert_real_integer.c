#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ __int64 ;
struct TYPE_4__ {double f; scalar_t__ i; } ;
struct TYPE_3__ {int const base; TYPE_2__ code; } ;

/* Variables and functions */
#define  IDC_RADIO_BIN 131 
#define  IDC_RADIO_DEC 130 
#define  IDC_RADIO_HEX 129 
#define  IDC_RADIO_OCT 128 
 int /*<<< orphan*/  apply_int_mask (TYPE_2__*) ; 
 TYPE_1__ calc ; 

void convert_real_integer(unsigned int base)
{
    switch (base) {
    case IDC_RADIO_DEC:
        calc.code.f = (double)calc.code.i;
        break;
    case IDC_RADIO_OCT:
    case IDC_RADIO_BIN:
    case IDC_RADIO_HEX:
        if (calc.base == IDC_RADIO_DEC) {
            calc.code.i = (__int64)calc.code.f;
            apply_int_mask(&calc.code);
        }
        break;
    }
}