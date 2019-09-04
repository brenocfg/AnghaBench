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
typedef  int ut64 ;
typedef  int st8 ;
struct TYPE_3__ {int o; int /*<<< orphan*/ * a; } ;
typedef  TYPE_1__ ArmOpcode ;

/* Variables and functions */
 int DOTW_BIT ; 
 int getreg (int /*<<< orphan*/ ) ; 
 int getregmemstart (int /*<<< orphan*/ ) ; 

__attribute__((used)) static st8 mem_16bit_2reg(ArmOpcode *ao, ut64 m) {
	ut8 rd = getreg (ao->a[0]);
	ut8 rn = getregmemstart (ao->a[1]);
	if ( (rd < 8) && (rn < 8) && !(m & DOTW_BIT)) {
		ao->o |= rd << 8;
		ao->o |= rn << 11;
		return 2;
	}
	return 0;
}