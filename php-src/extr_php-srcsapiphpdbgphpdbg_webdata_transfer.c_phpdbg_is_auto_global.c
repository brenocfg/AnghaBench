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
 int zend_is_auto_global (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_string_init (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int phpdbg_is_auto_global(char *name, int len) {
	int ret;
	zend_string *str = zend_string_init(name, len, 0);
	ret = zend_is_auto_global(str);
	zend_string_free(str);
	return ret;
}