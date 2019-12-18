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
struct dstr {size_t len; scalar_t__* array; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_ensure_capacity (struct dstr*,size_t const) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 

__attribute__((used)) static inline void dstr_resize(struct dstr *dst, const size_t num)
{
	if (!num) {
		dstr_free(dst);
		return;
	}

	dstr_ensure_capacity(dst, num + 1);
	dst->array[num] = 0;
	dst->len = num;
}