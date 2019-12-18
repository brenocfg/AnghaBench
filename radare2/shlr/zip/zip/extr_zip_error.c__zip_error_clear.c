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
struct zip_error {scalar_t__ sys_err; int /*<<< orphan*/  zip_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZIP_ER_OK ; 

void
_zip_error_clear(struct zip_error *err)
{
    if (err == NULL)
	return;

    err->zip_err = ZIP_ER_OK;
    err->sys_err = 0;
}