#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_5__ {scalar_t__ const member_1; scalar_t__ const member_0; scalar_t__ size; scalar_t__ addr; } ;
typedef  TYPE_1__ RInterval ;

/* Variables and functions */
 scalar_t__ R_MAX (scalar_t__,scalar_t__) ; 
 scalar_t__ R_MIN (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline RInterval r_itv_intersect(RInterval itv, RInterval x) {
	const ut64 addr = R_MAX (itv.addr, x.addr);
	const ut64 end = R_MIN (itv.addr + itv.size - 1, x.addr + x.size - 1) + 1;
	RInterval rai = {addr, end - addr};
	return rai;
}