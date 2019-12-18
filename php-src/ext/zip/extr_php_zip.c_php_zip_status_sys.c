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
typedef  int /*<<< orphan*/  zip_error_t ;
typedef  int zend_long ;
struct zip {int dummy; } ;

/* Variables and functions */
 int zip_error_code_system (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zip_error_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zip_error_get (struct zip*,int*,int*) ; 
 int /*<<< orphan*/ * zip_get_error (struct zip*) ; 

__attribute__((used)) static zend_long php_zip_status_sys(struct zip *za) /* {{{ */
{
#if LIBZIP_VERSION_MAJOR < 1
	int zep, syp;

	zip_error_get(za, &zep, &syp);
#else
	int syp;
	zip_error_t *err;

	err = zip_get_error(za);
	syp = zip_error_code_system(err);
	zip_error_fini(err);
#endif
	return syp;
}