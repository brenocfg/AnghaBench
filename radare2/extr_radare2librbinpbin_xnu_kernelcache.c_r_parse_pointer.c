#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ut64 ;
struct TYPE_8__ {TYPE_1__* rebase_info; } ;
struct TYPE_7__ {int address; } ;
struct TYPE_6__ {int kernel_base; } ;
typedef  TYPE_2__ RParsedPointer ;
typedef  TYPE_3__ RKernelCacheObj ;

/* Variables and functions */

__attribute__((used)) static bool r_parse_pointer(RParsedPointer *ptr, ut64 decorated_addr, RKernelCacheObj *obj) {
	/*
	 * Logic taken from:
	 * https://github.com/Synacktiv/kernelcache-laundering/blob/master/ios12_kernel_cache_helper.py
	 */

	if ((decorated_addr & 0x4000000000000000LL) == 0 && obj->rebase_info) {
		if (decorated_addr & 0x8000000000000000LL) {
			ptr->address = obj->rebase_info->kernel_base + (decorated_addr & 0xFFFFFFFFLL);
		} else {
			ptr->address = ((decorated_addr << 13) & 0xFF00000000000000LL) | (decorated_addr & 0x7ffffffffffLL);
			if (decorated_addr & 0x40000000000LL) {
				ptr->address |= 0xfffc0000000000LL;
			}
		}
	} else {
		ptr->address = decorated_addr;
	}

	return true;
}