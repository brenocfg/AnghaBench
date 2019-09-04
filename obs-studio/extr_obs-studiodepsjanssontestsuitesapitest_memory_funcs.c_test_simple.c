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
typedef  scalar_t__ json_malloc_t ;
typedef  scalar_t__ json_free_t ;

/* Variables and functions */
 int /*<<< orphan*/  create_and_free_complex_object () ; 
 int /*<<< orphan*/  fail (char*) ; 
 int free_called ; 
 int /*<<< orphan*/  json_get_alloc_funcs (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  json_set_alloc_funcs (scalar_t__,scalar_t__) ; 
 int malloc_called ; 
 scalar_t__ my_free ; 
 scalar_t__ my_malloc ; 

__attribute__((used)) static void test_simple()
{
    json_malloc_t mfunc = NULL;
    json_free_t ffunc = NULL;

    json_set_alloc_funcs(my_malloc, my_free);
    json_get_alloc_funcs(&mfunc, &ffunc);
    create_and_free_complex_object();

    if (malloc_called != 1 || free_called != 1
        || mfunc != my_malloc || ffunc != my_free)
        fail("Custom allocation failed");
}