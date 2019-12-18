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
struct st_mysqlnd_plugin_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mysqlnd_caching_sha2_auth_plugin ; 
 int /*<<< orphan*/  mysqlnd_native_auth_plugin ; 
 int /*<<< orphan*/  mysqlnd_pam_authentication_plugin ; 
 int /*<<< orphan*/  mysqlnd_plugin_register_ex (struct st_mysqlnd_plugin_header*) ; 
 int /*<<< orphan*/  mysqlnd_sha256_authentication_plugin ; 

void
mysqlnd_register_builtin_authentication_plugins(void)
{
	mysqlnd_plugin_register_ex((struct st_mysqlnd_plugin_header *) &mysqlnd_native_auth_plugin);
	mysqlnd_plugin_register_ex((struct st_mysqlnd_plugin_header *) &mysqlnd_pam_authentication_plugin);
#ifdef MYSQLND_HAVE_SSL
	mysqlnd_plugin_register_ex((struct st_mysqlnd_plugin_header *) &mysqlnd_caching_sha2_auth_plugin);
	mysqlnd_plugin_register_ex((struct st_mysqlnd_plugin_header *) &mysqlnd_sha256_authentication_plugin);
#endif
}