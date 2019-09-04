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
struct zip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  zip_error_get (struct zip*,int*,int*) ; 

__attribute__((used)) static int php_zip_status(struct zip *za) /* {{{ */
{
#if LIBZIP_VERSION_MAJOR < 1
	int zep, syp;

	zip_error_get(za, &zep, &syp);
#else
	int zep;
	zip_error_t *err;

	err = zip_get_error(za);
	zep = zip_error_code_zip(err);
	zip_error_fini(err);
#endif
	return zep;
}