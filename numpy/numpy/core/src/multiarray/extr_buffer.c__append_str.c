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
typedef  int /*<<< orphan*/  _tmp_string_t ;

/* Variables and functions */
 scalar_t__ _append_char (int /*<<< orphan*/ *,char const) ; 

__attribute__((used)) static int
_append_str(_tmp_string_t *s, char const *p)
{
    for (; *p != '\0'; p++) {
        if (_append_char(s, *p) < 0) {
            return -1;
        }
    }
    return 0;
}