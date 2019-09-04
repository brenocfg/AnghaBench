#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
typedef  long long ut64 ;
struct TYPE_7__ {long long old; int cur; TYPE_1__* anal; } ;
struct TYPE_6__ {int /*<<< orphan*/  reg; } ;
typedef  TYPE_2__ RAnalEsil ;

/* Variables and functions */
 int /*<<< orphan*/  r_anal_esil_reg_read (TYPE_2__*,char*,long long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_anal_esil_reg_write (TYPE_2__*,char*,long long) ; 

__attribute__((used)) static int gb_custom_daa (RAnalEsil *esil) {
	ut8 a, H, C, Z;
	ut64 n;
	if (!esil || !esil->anal || !esil->anal->reg) {
		return false;
	}
	r_anal_esil_reg_read (esil, "H", &n, NULL);
	H = (ut8)n;
	r_anal_esil_reg_read (esil, "C", &n, NULL);
	C = (ut8)n;
	r_anal_esil_reg_read (esil, "a", &n, NULL);
	esil->old = n;
	a = (ut8)n;
	r_anal_esil_reg_read (esil, "N", &n, NULL);
	if (n) {
		if (C) {
			a = (a - 0x60) & 0xff;
		} else {
			r_anal_esil_reg_write (esil, "C", 0LL);
		}
		if (H) {
			a = (a - 0x06) & 0xff;
		}
	} else {
		if (C || (a > 0x99)) {
			a = (a + 0x60) & 0xff;
			r_anal_esil_reg_write (esil, "C", 1LL);
		}
		if (H || ((a & 0x0f) > 0x09)) {
			a += 0x06;
		};
	}
	esil->cur = a;
	Z = (a == 0);
	r_anal_esil_reg_write (esil, "a", (ut64)a);
	r_anal_esil_reg_write (esil, "Z", (ut64)Z);
	r_anal_esil_reg_write (esil, "H", 0LL);
	return true;
}