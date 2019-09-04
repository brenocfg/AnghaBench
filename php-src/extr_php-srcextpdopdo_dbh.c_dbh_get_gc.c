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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_3__ {int /*<<< orphan*/  def_stmt_ctor_args; } ;
typedef  TYPE_1__ pdo_dbh_t ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 TYPE_1__* php_pdo_dbh_fetch_inner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_std_get_properties (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HashTable *dbh_get_gc(zend_object *object, zval **gc_data, int *gc_count)
{
	pdo_dbh_t *dbh = php_pdo_dbh_fetch_inner(object);
	*gc_data = &dbh->def_stmt_ctor_args;
	*gc_count = 1;
	return zend_std_get_properties(object);
}