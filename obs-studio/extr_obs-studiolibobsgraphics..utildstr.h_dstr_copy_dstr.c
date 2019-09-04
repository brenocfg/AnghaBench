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
struct dstr {scalar_t__ len; scalar_t__ array; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_ensure_capacity (struct dstr*,scalar_t__) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void dstr_copy_dstr(struct dstr *dst, const struct dstr *src)
{
	if (dst->array)
		dstr_free(dst);

	if (src->len) {
		dstr_ensure_capacity(dst, src->len + 1);
		memcpy(dst->array, src->array, src->len + 1);
		dst->len = src->len;
	}
}