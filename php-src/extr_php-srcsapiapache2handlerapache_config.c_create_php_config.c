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
struct TYPE_3__ {int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ php_conf_rec ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_entry_dtor ; 
 int /*<<< orphan*/  destroy_php_config ; 
 int /*<<< orphan*/  phpapdebug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  zend_hash_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void *create_php_config(apr_pool_t *p, char *dummy)
{
	php_conf_rec *newx = (php_conf_rec *) apr_pcalloc(p, sizeof(*newx));

	phpapdebug((stderr, "Creating new config (%p) for %s\n", newx, dummy));
	zend_hash_init(&newx->config, 0, NULL, config_entry_dtor, 1);
	apr_pool_cleanup_register(p, newx, destroy_php_config, apr_pool_cleanup_null);
	return (void *) newx;
}