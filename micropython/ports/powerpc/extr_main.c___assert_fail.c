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
 int /*<<< orphan*/  printf (char*,char const*,unsigned int,char const*,char const*) ; 

void __assert_fail(const char *__assertion, const char *__file,
    unsigned int __line, const char *__function) {
    printf("Assert at %s:%d:%s() \"%s\" failed\n", __file, __line, __function, __assertion);
    for (;;) ;
}