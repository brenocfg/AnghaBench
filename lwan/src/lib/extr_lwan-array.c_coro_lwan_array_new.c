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
struct lwan_array {int dummy; } ;
struct coro {int dummy; } ;

/* Variables and functions */
 scalar_t__ LIKELY (struct lwan_array*) ; 
 int /*<<< orphan*/  coro_lwan_array_free_heap ; 
 int /*<<< orphan*/  coro_lwan_array_free_inline ; 
 struct lwan_array* coro_malloc_full (struct coro*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lwan_array_init (struct lwan_array*) ; 

struct lwan_array *coro_lwan_array_new(struct coro *coro, bool inline_first)
{
    struct lwan_array *array;

    array = coro_malloc_full(coro, sizeof(*array),
                             inline_first ? coro_lwan_array_free_inline
                                          : coro_lwan_array_free_heap);
    if (LIKELY(array))
        lwan_array_init(array);

    return array;
}