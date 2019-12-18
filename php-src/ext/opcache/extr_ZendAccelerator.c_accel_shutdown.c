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
struct TYPE_3__ {int /*<<< orphan*/  on_modify; } ;
typedef  TYPE_1__ zend_ini_entry ;
typedef  scalar_t__ zend_bool ;

/* Variables and functions */
 int /*<<< orphan*/  EG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZCG (int /*<<< orphan*/ ) ; 
 scalar_t__ ZCSG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  accel_blacklist ; 
 int /*<<< orphan*/  accel_globals_id ; 
 int /*<<< orphan*/  accel_post_shutdown ; 
 int /*<<< orphan*/  accel_reset_pcre_cache () ; 
 int /*<<< orphan*/  accel_startup_ok ; 
 int /*<<< orphan*/  accelerator_orig_compile_file ; 
 int /*<<< orphan*/  enabled ; 
 scalar_t__ file_cache_only ; 
 int /*<<< orphan*/  ini_directives ; 
 int /*<<< orphan*/  orig_include_path_on_modify ; 
 int /*<<< orphan*/  orig_post_shutdown_cb ; 
 int /*<<< orphan*/  preload_script ; 
 int /*<<< orphan*/  preload_shutdown () ; 
 int /*<<< orphan*/  ts_free_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_accel_blacklist_shutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_compile_file ; 
 TYPE_1__* zend_hash_str_find_ptr (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  zend_jit_shutdown () ; 
 int /*<<< orphan*/  zend_optimizer_shutdown () ; 
 int /*<<< orphan*/  zend_post_shutdown_cb ; 

void accel_shutdown(void)
{
	zend_ini_entry *ini_entry;
	zend_bool _file_cache_only = 0;

#ifdef HAVE_JIT
	zend_jit_shutdown();
#endif

	zend_optimizer_shutdown();

	zend_accel_blacklist_shutdown(&accel_blacklist);

	if (!ZCG(enabled) || !accel_startup_ok) {
#ifdef ZTS
		ts_free_id(accel_globals_id);
#endif
		return;
	}

	if (ZCSG(preload_script)) {
		preload_shutdown();
	}

	_file_cache_only = file_cache_only;

	accel_reset_pcre_cache();

#ifdef ZTS
	ts_free_id(accel_globals_id);
#endif

	if (!_file_cache_only) {
		/* Delay SHM dettach */
		orig_post_shutdown_cb = zend_post_shutdown_cb;
		zend_post_shutdown_cb = accel_post_shutdown;
	}

	zend_compile_file = accelerator_orig_compile_file;

	if ((ini_entry = zend_hash_str_find_ptr(EG(ini_directives), "include_path", sizeof("include_path")-1)) != NULL) {
		ini_entry->on_modify = orig_include_path_on_modify;
	}
}