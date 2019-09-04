#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_8__ {TYPE_1__* methods; scalar_t__ is_persistent; scalar_t__ in_txn; } ;
typedef  TYPE_2__ pdo_dbh_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* persistent_shutdown ) (TYPE_2__*) ;int /*<<< orphan*/  (* rollback ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dbh_free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* php_pdo_dbh_fetch_inner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_object_std_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pdo_dbh_free_storage(zend_object *std)
{
	pdo_dbh_t *dbh = php_pdo_dbh_fetch_inner(std);
	if (dbh->in_txn && dbh->methods && dbh->methods->rollback) {
		dbh->methods->rollback(dbh);
		dbh->in_txn = 0;
	}

	if (dbh->is_persistent && dbh->methods && dbh->methods->persistent_shutdown) {
		dbh->methods->persistent_shutdown(dbh);
	}
	zend_object_std_dtor(std);
	dbh_free(dbh, 0);
}