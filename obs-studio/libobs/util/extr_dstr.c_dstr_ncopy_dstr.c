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
struct dstr {size_t len; size_t capacity; scalar_t__* array; } ;

/* Variables and functions */
 scalar_t__* bmemdup (scalar_t__*,size_t) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 size_t size_min (size_t const,size_t) ; 

void dstr_ncopy_dstr(struct dstr *dst, const struct dstr *str, const size_t len)
{
	size_t newlen;

	if (dst->array)
		dstr_free(dst);

	if (!len)
		return;

	newlen = size_min(len, str->len);
	dst->array = bmemdup(str->array, newlen + 1);
	dst->len = newlen;
	dst->capacity = newlen + 1;

	dst->array[newlen] = 0;
}