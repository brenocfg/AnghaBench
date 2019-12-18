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

/* Variables and functions */
 int /*<<< orphan*/  create_and_free_complex_object () ; 
 int /*<<< orphan*/  json_set_alloc_funcs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  secure_free ; 
 int /*<<< orphan*/  secure_malloc ; 

__attribute__((used)) static void test_secure_funcs(void)
{
    json_set_alloc_funcs(secure_malloc, secure_free);
    create_and_free_complex_object();
}