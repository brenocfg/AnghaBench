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
 int MP_ARRAY_SIZE (char**) ; 
 char** err_table ; 

const char *mpv_error_string(int error)
{
    error = -error;
    if (error < 0)
        error = 0;
    const char *name = NULL;
    if (error < MP_ARRAY_SIZE(err_table))
        name = err_table[error];
    return name ? name : "unknown error";
}