#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct meta_obj {int len; scalar_t__ value; } ;

/* Variables and functions */
 int memcmp (void*,void*,int) ; 

__attribute__((used)) static int meta_var_compare(struct meta_obj *a, struct meta_obj *b)
{
	int r = a->len - b->len;

	if (r == 0)
		r = memcmp((void *) a->value, (void *) b->value, a->len);

	return r;
}