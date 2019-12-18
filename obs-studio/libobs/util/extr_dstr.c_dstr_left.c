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
typedef  struct dstr {int /*<<< orphan*/  array; } const dstr ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_resize (struct dstr const*,size_t const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t const) ; 

void dstr_left(struct dstr *dst, const struct dstr *str, const size_t pos)
{
	dstr_resize(dst, pos);
	if (dst != str)
		memcpy(dst->array, str->array, pos);
}