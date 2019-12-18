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
 scalar_t__ ERR_get_next_error_library () ; 
 int /*<<< orphan*/  ERR_raise (scalar_t__,int) ; 
 int /*<<< orphan*/  ERR_set_debug (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ lib_code ; 

__attribute__((used)) static void ERR_AFALG_error(int function, int reason, char *file, int line)
{
    if (lib_code == 0)
        lib_code = ERR_get_next_error_library();
    ERR_raise(lib_code, reason);
    ERR_set_debug(file, line, NULL);
}