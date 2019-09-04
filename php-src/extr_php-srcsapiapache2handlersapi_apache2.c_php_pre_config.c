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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APLOG_CRIT ; 
 int /*<<< orphan*/  APLOG_MARK ; 
 int /*<<< orphan*/  AP_MPMQ_IS_THREADED ; 
 int DONE ; 
 int OK ; 
 int /*<<< orphan*/  ap_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ap_mpm_query (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * apache2_php_ini_path_override ; 

__attribute__((used)) static int php_pre_config(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptemp)
{
#ifndef ZTS
	int threaded_mpm;

	ap_mpm_query(AP_MPMQ_IS_THREADED, &threaded_mpm);
	if(threaded_mpm) {
		ap_log_error(APLOG_MARK, APLOG_CRIT, 0, 0, "Apache is running a threaded MPM, but your PHP Module is not compiled to be threadsafe.  You need to recompile PHP.");
		return DONE;
	}
#endif
	/* When this is NULL, apache won't override the hard-coded default
	 * php.ini path setting. */
	apache2_php_ini_path_override = NULL;
	return OK;
}