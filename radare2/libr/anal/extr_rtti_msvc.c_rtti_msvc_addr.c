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
typedef  scalar_t__ ut32 ;
struct TYPE_3__ {int word_size; } ;
typedef  TYPE_1__ RVTableContext ;

/* Variables and functions */

__attribute__((used)) static inline ut64 rtti_msvc_addr(RVTableContext *context, ut64 col_addr, ut64 col_base, ut32 addr) {
	if (context->word_size != 8) {
		return addr;
	}
	return addr + (col_addr - col_base);
}