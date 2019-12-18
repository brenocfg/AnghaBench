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
struct point2d {int dummy; } ;
struct outline {int count; struct point2d* items; } ;
struct dynamic_array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  reserve (struct dynamic_array*,int,int) ; 

__attribute__((used)) static struct point2d *add_points(struct outline *array, int num)
{
    struct point2d *item;

    if (!reserve((struct dynamic_array *)array, array->count + num, sizeof(array->items[0])))
        return NULL;

    item = &array->items[array->count];
    array->count += num;
    return item;
}