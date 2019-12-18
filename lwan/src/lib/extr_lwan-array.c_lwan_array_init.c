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
struct lwan_array {scalar_t__ elements; int /*<<< orphan*/ * base; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ UNLIKELY (int) ; 

int lwan_array_init(struct lwan_array *a)
{
    if (UNLIKELY(!a))
        return -EINVAL;

    a->base = NULL;
    a->elements = 0;

    return 0;
}