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
struct darray {scalar_t__ capacity; scalar_t__ num; int /*<<< orphan*/ * array; } ;

/* Variables and functions */

__attribute__((used)) static inline void darray_init(struct darray *dst)
{
	dst->array    = NULL;
	dst->num      = 0;
	dst->capacity = 0;
}