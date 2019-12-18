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
struct zip_error {int /*<<< orphan*/  sys_err; int /*<<< orphan*/  zip_err; } ;

/* Variables and functions */

void
_zip_error_copy(struct zip_error *dst, const struct zip_error *src)
{
    dst->zip_err = src->zip_err;
    dst->sys_err = src->sys_err;
}