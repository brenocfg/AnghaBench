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
struct TYPE_4__ {int did; } ;
struct TYPE_3__ {int did; } ;
union msr_pstate {int val; TYPE_2__ bits; TYPE_1__ fam17h_bits; } ;

/* Variables and functions */

__attribute__((used)) static int get_did(int family, union msr_pstate pstate)
{
	int t;

	if (family == 0x12)
		t = pstate.val & 0xf;
	else if (family == 0x17)
		t = pstate.fam17h_bits.did;
	else
		t = pstate.bits.did;

	return t;
}