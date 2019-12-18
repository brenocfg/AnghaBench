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
struct zip_error {int dummy; } ;

/* Variables and functions */
 scalar_t__ ZIP_ET_SYS ; 
 int /*<<< orphan*/  _zip_error_get (struct zip_error const*,int*,int*) ; 
 int errno ; 
 scalar_t__ zip_error_get_sys_type (int) ; 

__attribute__((used)) static void
set_error(int *zep, const struct zip_error *err, int ze)
{
    int se;

    if (err) {
	_zip_error_get(err, &ze, &se);
	if (zip_error_get_sys_type(ze) == ZIP_ET_SYS)
	    errno = se;
    }

    if (zep)
	*zep = ze;
}