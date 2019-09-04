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

/* Variables and functions */
 int SUCCESS ; 
 int /*<<< orphan*/  configuration_hash ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * php_ini_opened_path ; 
 int /*<<< orphan*/ * php_ini_scanned_files ; 
 int /*<<< orphan*/  zend_hash_destroy (int /*<<< orphan*/ *) ; 

int php_shutdown_config(void)
{
	zend_hash_destroy(&configuration_hash);
	if (php_ini_opened_path) {
		free(php_ini_opened_path);
		php_ini_opened_path = NULL;
	}
	if (php_ini_scanned_files) {
		free(php_ini_scanned_files);
		php_ini_scanned_files = NULL;
	}
	return SUCCESS;
}