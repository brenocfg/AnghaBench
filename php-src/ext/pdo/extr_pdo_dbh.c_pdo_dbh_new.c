#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * handlers; } ;
typedef  TYPE_1__ zend_object ;
typedef  int /*<<< orphan*/  zend_class_entry ;
typedef  int /*<<< orphan*/  pdo_dbh_t ;
struct TYPE_10__ {TYPE_1__ std; TYPE_8__* inner; } ;
typedef  TYPE_2__ pdo_dbh_object_t ;
struct TYPE_11__ {int /*<<< orphan*/  def_stmt_ce; } ;

/* Variables and functions */
 TYPE_8__* ecalloc (int,int) ; 
 int /*<<< orphan*/  object_properties_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdo_dbh_object_handlers ; 
 int /*<<< orphan*/  pdo_dbstmt_ce ; 
 int /*<<< orphan*/  rebuild_object_properties (TYPE_1__*) ; 
 TYPE_2__* zend_object_alloc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_object_std_init (TYPE_1__*,int /*<<< orphan*/ *) ; 

zend_object *pdo_dbh_new(zend_class_entry *ce)
{
	pdo_dbh_object_t *dbh;

	dbh = zend_object_alloc(sizeof(pdo_dbh_object_t), ce);
	zend_object_std_init(&dbh->std, ce);
	object_properties_init(&dbh->std, ce);
	rebuild_object_properties(&dbh->std);
	dbh->inner = ecalloc(1, sizeof(pdo_dbh_t));
	dbh->inner->def_stmt_ce = pdo_dbstmt_ce;

	dbh->std.handlers = &pdo_dbh_object_handlers;

	return &dbh->std;
}