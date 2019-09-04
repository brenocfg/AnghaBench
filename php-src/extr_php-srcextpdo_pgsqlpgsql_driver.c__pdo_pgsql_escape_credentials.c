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
typedef  int /*<<< orphan*/  zend_string ;

/* Variables and functions */
 int /*<<< orphan*/ * php_addcslashes_str (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static zend_string* _pdo_pgsql_escape_credentials(char *str)
{
	if (str) {
		return php_addcslashes_str(str, strlen(str), "\\'", sizeof("\\'"));
	}

	return NULL;
}