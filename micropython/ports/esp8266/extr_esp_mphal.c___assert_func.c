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
 int /*<<< orphan*/  mp_raise_msg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mp_type_AssertionError ; 
 int /*<<< orphan*/  printf (char*,char const*,int,char const*,char const*) ; 

void __assert_func(const char *file, int line, const char *func, const char *expr) {
    printf("assert:%s:%d:%s: %s\n", file, line, func, expr);
    mp_raise_msg(&mp_type_AssertionError, "C-level assert");
}