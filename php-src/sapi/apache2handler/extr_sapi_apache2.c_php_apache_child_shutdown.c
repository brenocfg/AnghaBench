#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  apr_status_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* shutdown ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 TYPE_1__ apache2_sapi_module ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  tsrm_shutdown () ; 

__attribute__((used)) static apr_status_t php_apache_child_shutdown(void *tmp)
{
	apache2_sapi_module.shutdown(&apache2_sapi_module);
#if defined(ZTS) && !defined(PHP_WIN32)
	tsrm_shutdown();
#endif
	return APR_SUCCESS;
}