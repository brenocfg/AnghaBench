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
typedef  int /*<<< orphan*/  server_rec ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_apache_child_shutdown ; 

__attribute__((used)) static void php_apache_child_init(apr_pool_t *pchild, server_rec *s)
{
	apr_pool_cleanup_register(pchild, NULL, php_apache_child_shutdown, apr_pool_cleanup_null);
}