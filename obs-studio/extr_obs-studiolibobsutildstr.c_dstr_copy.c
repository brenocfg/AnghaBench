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
struct dstr {size_t len; int /*<<< orphan*/  array; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_ensure_capacity (struct dstr*,size_t) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 size_t strlen (char const*) ; 

void dstr_copy(struct dstr *dst, const char *array)
{
	size_t len;

	if (!array || !*array) {
		dstr_free(dst);
		return;
	}

	len = strlen(array);
	dstr_ensure_capacity(dst, len + 1);
	memcpy(dst->array, array, len + 1);
	dst->len = len;
}