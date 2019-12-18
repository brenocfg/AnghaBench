#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int shift; } ;
struct meta_value {int val; TYPE_1__ hdr; } ;
struct meta_obj {int value; } ;

/* Variables and functions */

__attribute__((used)) static void meta_int_apply_extras(struct meta_value *v,
				  struct meta_obj *dst)
{
	if (v->hdr.shift)
		dst->value >>= v->hdr.shift;

	if (v->val)
		dst->value &= v->val;
}