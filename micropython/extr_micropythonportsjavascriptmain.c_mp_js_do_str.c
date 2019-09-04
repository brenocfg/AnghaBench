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
 int /*<<< orphan*/  MP_PARSE_FILE_INPUT ; 
 int do_str (char const*,int /*<<< orphan*/ ) ; 

int mp_js_do_str(const char *code) {
    return do_str(code, MP_PARSE_FILE_INPUT);
}