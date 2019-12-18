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
struct lwan_array {int /*<<< orphan*/  elements; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 scalar_t__ LIKELY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int (*) (void const*,void const*)) ; 

void lwan_array_sort(struct lwan_array *a,
                     size_t element_size,
                     int (*cmp)(const void *a, const void *b))
{
    if (LIKELY(a->elements))
        qsort(a->base, a->elements, element_size, cmp);
}