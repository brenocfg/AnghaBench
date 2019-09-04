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
typedef  int /*<<< orphan*/  zend_bool ;

/* Variables and functions */
 int /*<<< orphan*/  safe_php_register_variable (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void register_http_post_files_variable(char *strvar, char *val, zval *http_post_files, zend_bool override_protection) /* {{{ */
{
	safe_php_register_variable(strvar, val, strlen(val), http_post_files, override_protection);
}