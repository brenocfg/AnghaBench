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
 int /*<<< orphan*/  r_cons_printf (char*,char const*,char const*) ; 

__attribute__((used)) static int listOpDescriptions(void *_core, const char *k, const char *v) {
        r_cons_printf ("%s=%s\n", k, v);
        return 1;
}