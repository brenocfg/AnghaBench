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
typedef  int uint8_t ;
struct TYPE_3__ {int* bits; } ;
struct TYPE_4__ {TYPE_1__ nkro; } ;

/* Variables and functions */
 TYPE_2__* keyboard_report ; 

__attribute__((used)) static bool key_down(uint8_t code) {
    return (keyboard_report->nkro.bits[code>>3] & 1<<(code&7)) != 0;
}