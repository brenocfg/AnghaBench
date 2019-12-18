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
 int /*<<< orphan*/  APR_HOOK_MIDDLE ; 
 int /*<<< orphan*/  ap_hook_child_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ap_hook_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ap_hook_post_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ap_hook_pre_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_apache_child_init ; 
 int /*<<< orphan*/  php_apache_server_startup ; 
 int /*<<< orphan*/  php_apache_signal_init ; 
 int /*<<< orphan*/  php_handler ; 
 int /*<<< orphan*/  php_pre_config ; 

void php_ap2_register_hook(apr_pool_t *p)
{
	ap_hook_pre_config(php_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
	ap_hook_post_config(php_apache_server_startup, NULL, NULL, APR_HOOK_MIDDLE);
	ap_hook_handler(php_handler, NULL, NULL, APR_HOOK_MIDDLE);
#ifdef ZEND_SIGNALS
	ap_hook_child_init(php_apache_signal_init, NULL, NULL, APR_HOOK_MIDDLE);
#endif
	ap_hook_child_init(php_apache_child_init, NULL, NULL, APR_HOOK_MIDDLE);
}