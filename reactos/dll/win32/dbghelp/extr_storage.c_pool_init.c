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
struct pool {size_t arena_size; int /*<<< orphan*/  arena_full; int /*<<< orphan*/  arena_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 

void pool_init(struct pool* a, size_t arena_size)
{
    list_init( &a->arena_list );
    list_init( &a->arena_full );
    a->arena_size = arena_size;
}