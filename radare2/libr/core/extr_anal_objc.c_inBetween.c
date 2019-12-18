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
typedef  scalar_t__ ut64 ;
struct TYPE_3__ {scalar_t__ vsize; scalar_t__ vaddr; } ;
typedef  TYPE_1__ RBinSection ;

/* Variables and functions */
 int R_BETWEEN (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ UT64_MAX ; 

__attribute__((used)) static bool inBetween(RBinSection *s, ut64 addr) {
	if (!s || addr == UT64_MAX) {
		return false;
	}
	ut64 from = s->vaddr;
	ut64 to = from + s->vsize;
	return R_BETWEEN (from, addr, to);
}