#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* r; } ;
typedef  TYPE_2__ php_struct ;
struct TYPE_4__ {int /*<<< orphan*/  subprocess_env; } ;

/* Variables and functions */
 TYPE_2__* SG (int /*<<< orphan*/ ) ; 
 char* apr_table_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  server_context ; 

__attribute__((used)) static char *
php_apache_sapi_getenv(char *name, size_t name_len)
{
	php_struct *ctx = SG(server_context);
	const char *env_var;

	if (ctx == NULL) {
		return NULL;
	}

	env_var = apr_table_get(ctx->r->subprocess_env, name);

	return (char *) env_var;
}