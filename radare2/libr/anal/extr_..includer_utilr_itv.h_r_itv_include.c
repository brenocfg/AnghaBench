#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_4__ {scalar_t__ addr; scalar_t__ size; } ;
typedef  TYPE_1__ RInterval ;

/* Variables and functions */

__attribute__((used)) static inline bool r_itv_include(RInterval itv, RInterval x) {
	const ut64 end = itv.addr + itv.size;
	return itv.addr <= x.addr && (!end || (x.addr + x.size && x.addr + x.size <= end));
}