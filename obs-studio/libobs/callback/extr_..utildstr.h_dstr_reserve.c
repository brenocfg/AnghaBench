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
struct dstr {size_t const len; char* array; size_t capacity; } ;

/* Variables and functions */
 scalar_t__ brealloc (char*,size_t const) ; 

__attribute__((used)) static inline void dstr_reserve(struct dstr *dst, const size_t capacity)
{
	if (capacity == 0 || capacity <= dst->len)
		return;

	dst->array = (char *)brealloc(dst->array, capacity);
	dst->capacity = capacity;
}