#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
typedef  scalar_t__ ut32 ;
struct TYPE_3__ {int /*<<< orphan*/  reg; } ;
typedef  TYPE_1__ RAnal ;

/* Variables and functions */
 scalar_t__ i8051_reg_read (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ut32 map_direct_addr(RAnal *anal, ut8 addr) {
	if (addr < 0x80) {
		return addr + i8051_reg_read (anal->reg, "_idata");
	} else {
		return addr + i8051_reg_read (anal->reg, "_sfr");
	}
}