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
typedef  int /*<<< orphan*/  zval ;

/* Variables and functions */
 int /*<<< orphan*/  php_import_environment_variables (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void php_embed_register_variables(zval *track_vars_array)
{
	php_import_environment_variables(track_vars_array);
}