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
typedef  int /*<<< orphan*/  vstr_t ;

/* Variables and functions */
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  vstr_add_strn (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

void vstr_add_str(vstr_t *vstr, const char *str) {
    vstr_add_strn(vstr, str, strlen(str));
}