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
struct zip_error {int zip_err; int sys_err; } ;

/* Variables and functions */
 scalar_t__ ZIP_ET_NONE ; 
 scalar_t__ zip_error_get_sys_type (int) ; 

void
_zip_error_get(const struct zip_error *err, int *zep, int *sep)
{
    if (zep)
	*zep = err->zip_err;
    if (sep) {
	if (zip_error_get_sys_type(err->zip_err) != ZIP_ET_NONE)
	    *sep = err->sys_err;
	else
	    *sep = 0;
    }
}