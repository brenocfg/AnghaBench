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

/* Variables and functions */
 int /*<<< orphan*/  free (struct lwan_array*) ; 
 int /*<<< orphan*/  lwan_array_reset (struct lwan_array*,struct lwan_array*) ; 

__attribute__((used)) static void coro_lwan_array_free_inline(void *data)
{
    struct lwan_array *array = data;

    lwan_array_reset(array, array + 1);
    free(array);
}