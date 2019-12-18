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
struct TYPE_4__ {int fid; } ;
struct TYPE_3__ {int fid; } ;
union msr_pstate {TYPE_2__ bits; TYPE_1__ fam17h_bits; } ;

/* Variables and functions */
 int get_did (int,union msr_pstate) ; 

__attribute__((used)) static int get_cof(int family, union msr_pstate pstate)
{
	int t;
	int fid, did, cof;

	did = get_did(family, pstate);
	if (family == 0x17 || family == 0x18) {
		fid = pstate.fam17h_bits.fid;
		cof = 200 * fid / did;
	} else {
		t = 0x10;
		fid = pstate.bits.fid;
		if (family == 0x11)
			t = 0x8;
		cof = (100 * (fid + t)) >> did;
	}
	return cof;
}