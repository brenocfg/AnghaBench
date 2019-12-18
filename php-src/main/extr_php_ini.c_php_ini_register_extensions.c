#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  functions; int /*<<< orphan*/  engine; } ;

/* Variables and functions */
 TYPE_1__ extension_lists ; 
 int /*<<< orphan*/  php_load_php_extension_cb ; 
 int /*<<< orphan*/  php_load_zend_extension_cb ; 
 int /*<<< orphan*/  zend_llist_apply (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_llist_destroy (int /*<<< orphan*/ *) ; 

void php_ini_register_extensions(void)
{
	zend_llist_apply(&extension_lists.engine, php_load_zend_extension_cb);
	zend_llist_apply(&extension_lists.functions, php_load_php_extension_cb);

	zend_llist_destroy(&extension_lists.engine);
	zend_llist_destroy(&extension_lists.functions);
}