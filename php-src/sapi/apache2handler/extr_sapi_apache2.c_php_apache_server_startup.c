#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* process; } ;
typedef  TYPE_2__ server_rec ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_9__ {scalar_t__ (* startup ) (TYPE_3__*) ;scalar_t__ php_ini_path_override; } ;
struct TYPE_7__ {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int DONE ; 
 int OK ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  ZEND_TSRMLS_CACHE_UPDATE () ; 
 scalar_t__ apache2_php_ini_path_override ; 
 TYPE_3__ apache2_sapi_module ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pool_userdata_get (void**,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pool_userdata_set (void const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_apache_add_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_apache_server_shutdown ; 
 int /*<<< orphan*/  php_tsrm_startup () ; 
 int /*<<< orphan*/  sapi_startup (TYPE_3__*) ; 
 scalar_t__ stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  zend_signal_startup () ; 

__attribute__((used)) static int
php_apache_server_startup(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptemp, server_rec *s)
{
	void *data = NULL;
	const char *userdata_key = "apache2hook_post_config";

	/* Apache will load, unload and then reload a DSO module. This
	 * prevents us from starting PHP until the second load. */
	apr_pool_userdata_get(&data, userdata_key, s->process->pool);
	if (data == NULL) {
		/* We must use set() here and *not* setn(), otherwise the
		 * static string pointed to by userdata_key will be mapped
		 * to a different location when the DSO is reloaded and the
		 * pointers won't match, causing get() to return NULL when
		 * we expected it to return non-NULL. */
		apr_pool_userdata_set((const void *)1, userdata_key, apr_pool_cleanup_null, s->process->pool);
		return OK;
	}

	/* Set up our overridden path. */
	if (apache2_php_ini_path_override) {
		apache2_sapi_module.php_ini_path_override = apache2_php_ini_path_override;
	}
#ifdef ZTS
	php_tsrm_startup();
# ifdef PHP_WIN32
	ZEND_TSRMLS_CACHE_UPDATE();
# endif
#endif

	zend_signal_startup();

	sapi_startup(&apache2_sapi_module);
	if (apache2_sapi_module.startup(&apache2_sapi_module) != SUCCESS) {
		return DONE;
	}
	apr_pool_cleanup_register(pconf, NULL, php_apache_server_shutdown, apr_pool_cleanup_null);
	php_apache_add_version(pconf);

	return OK;
}