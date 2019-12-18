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
struct meta_value {TYPE_1__ hdr; } ;
struct meta_obj {int len; } ;

/* Variables and functions */

__attribute__((used)) static void meta_var_apply_extras(struct meta_value *v,
				  struct meta_obj *dst)
{
	int shift = v->hdr.shift;

	if (shift && shift < dst->len)
		dst->len -= shift;
}