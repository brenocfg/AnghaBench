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
struct dstr {size_t len; scalar_t__ array; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_ensure_capacity (struct dstr*,size_t) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 

void dstr_cat_dstr(struct dstr *dst, const struct dstr *str)
{
	size_t new_len;
	if (!str->len)
		return;

	new_len = dst->len + str->len;

	dstr_ensure_capacity(dst, new_len + 1);
	memcpy(dst->array + dst->len, str->array, str->len + 1);
	dst->len = new_len;
}