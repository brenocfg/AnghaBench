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
struct TYPE_4__ {unsigned int l; int /*<<< orphan*/  h; } ;
typedef  TYPE_1__ ppe_u64_t ;

/* Variables and functions */

__attribute__((used)) static inline void u64_add_u32(ppe_u64_t opt1, unsigned int opt2, ppe_u64_t *ret)
{
	ret->l = opt1.l + opt2;
	if ( ret->l < opt1.l || ret->l < opt2 )
		ret->h++;
}