#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object_handlers ;
typedef  int /*<<< orphan*/  zend_class_entry ;
struct TYPE_10__ {void* unserialize; void* serialize; int /*<<< orphan*/  create_object; int /*<<< orphan*/  ce_flags; } ;
struct TYPE_9__ {int /*<<< orphan*/  compare; int /*<<< orphan*/  get_class_name; int /*<<< orphan*/  get_constructor; int /*<<< orphan*/  get_method; int /*<<< orphan*/  get_properties_for; int /*<<< orphan*/  unset_dimension; int /*<<< orphan*/  has_dimension; int /*<<< orphan*/  write_dimension; int /*<<< orphan*/  read_dimension; int /*<<< orphan*/  unset_property; int /*<<< orphan*/  has_property; int /*<<< orphan*/  write_property; int /*<<< orphan*/  read_property; int /*<<< orphan*/ * get_property_ptr_ptr; int /*<<< orphan*/ * clone_obj; int /*<<< orphan*/  free_obj; int /*<<< orphan*/  dtor_obj; int /*<<< orphan*/  offset; } ;
struct TYPE_8__ {void* unserialize; void* serialize; int /*<<< orphan*/  create_object; int /*<<< orphan*/  get_iterator; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_CLASS_ENTRY (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XtOffsetOf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_ACC_FINAL ; 
 int /*<<< orphan*/  ZEND_ACC_PUBLIC ; 
 int /*<<< orphan*/  dbstmt_compare ; 
 int /*<<< orphan*/  dbstmt_method_get ; 
 int /*<<< orphan*/  dbstmt_prop_delete ; 
 int /*<<< orphan*/  dbstmt_prop_write ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* pdo_dbstmt_ce ; 
 int /*<<< orphan*/  pdo_dbstmt_free_storage ; 
 int /*<<< orphan*/  pdo_dbstmt_functions ; 
 int /*<<< orphan*/  pdo_dbstmt_new ; 
 TYPE_3__ pdo_dbstmt_object_handlers ; 
 TYPE_4__* pdo_row_ce ; 
 int /*<<< orphan*/  pdo_row_free_storage ; 
 int /*<<< orphan*/  pdo_row_functions ; 
 int /*<<< orphan*/  pdo_row_new ; 
 TYPE_3__ pdo_row_object_handlers ; 
 int /*<<< orphan*/  pdo_stmt_iter_get ; 
 int /*<<< orphan*/  pdo_stmt_t ; 
 int /*<<< orphan*/  row_compare ; 
 int /*<<< orphan*/  row_dim_delete ; 
 int /*<<< orphan*/  row_dim_exists ; 
 int /*<<< orphan*/  row_dim_read ; 
 int /*<<< orphan*/  row_dim_write ; 
 int /*<<< orphan*/  row_get_classname ; 
 int /*<<< orphan*/  row_get_ctor ; 
 int /*<<< orphan*/  row_get_properties_for ; 
 int /*<<< orphan*/  row_method_get ; 
 int /*<<< orphan*/  row_prop_delete ; 
 int /*<<< orphan*/  row_prop_exists ; 
 int /*<<< orphan*/  row_prop_read ; 
 int /*<<< orphan*/  row_prop_write ; 
 int /*<<< orphan*/  std ; 
 int /*<<< orphan*/  std_object_handlers ; 
 int /*<<< orphan*/  zend_ce_traversable ; 
 int /*<<< orphan*/  zend_class_implements (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 void* zend_class_serialize_deny ; 
 void* zend_class_unserialize_deny ; 
 int /*<<< orphan*/  zend_declare_property_null (TYPE_1__*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_objects_destroy_object ; 
 void* zend_register_internal_class (int /*<<< orphan*/ *) ; 

void pdo_stmt_init(void)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "PDOStatement", pdo_dbstmt_functions);
	pdo_dbstmt_ce = zend_register_internal_class(&ce);
	pdo_dbstmt_ce->get_iterator = pdo_stmt_iter_get;
	pdo_dbstmt_ce->create_object = pdo_dbstmt_new;
	pdo_dbstmt_ce->serialize = zend_class_serialize_deny;
	pdo_dbstmt_ce->unserialize = zend_class_unserialize_deny;
	zend_class_implements(pdo_dbstmt_ce, 1, zend_ce_traversable);
	zend_declare_property_null(pdo_dbstmt_ce, "queryString", sizeof("queryString")-1, ZEND_ACC_PUBLIC);

	memcpy(&pdo_dbstmt_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
	pdo_dbstmt_object_handlers.offset = XtOffsetOf(pdo_stmt_t, std);
	pdo_dbstmt_object_handlers.dtor_obj = zend_objects_destroy_object;
	pdo_dbstmt_object_handlers.free_obj = pdo_dbstmt_free_storage;
	pdo_dbstmt_object_handlers.write_property = dbstmt_prop_write;
	pdo_dbstmt_object_handlers.unset_property = dbstmt_prop_delete;
	pdo_dbstmt_object_handlers.get_method = dbstmt_method_get;
	pdo_dbstmt_object_handlers.compare = dbstmt_compare;
	pdo_dbstmt_object_handlers.clone_obj = NULL;

	INIT_CLASS_ENTRY(ce, "PDORow", pdo_row_functions);
	pdo_row_ce = zend_register_internal_class(&ce);
	pdo_row_ce->ce_flags |= ZEND_ACC_FINAL; /* when removing this a lot of handlers need to be redone */
	pdo_row_ce->create_object = pdo_row_new;
	pdo_row_ce->serialize = zend_class_serialize_deny;
	pdo_row_ce->unserialize = zend_class_unserialize_deny;

	memcpy(&pdo_row_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
	pdo_row_object_handlers.free_obj = pdo_row_free_storage;
	pdo_row_object_handlers.clone_obj = NULL;
	pdo_row_object_handlers.get_property_ptr_ptr = NULL;
	pdo_row_object_handlers.read_property = row_prop_read;
	pdo_row_object_handlers.write_property = row_prop_write;
	pdo_row_object_handlers.has_property = row_prop_exists;
	pdo_row_object_handlers.unset_property = row_prop_delete;
	pdo_row_object_handlers.read_dimension = row_dim_read;
	pdo_row_object_handlers.write_dimension = row_dim_write;
	pdo_row_object_handlers.has_dimension = row_dim_exists;
	pdo_row_object_handlers.unset_dimension = row_dim_delete;
	pdo_row_object_handlers.get_properties_for = row_get_properties_for;
	pdo_row_object_handlers.get_method = row_method_get;
	pdo_row_object_handlers.get_constructor = row_get_ctor;
	pdo_row_object_handlers.get_class_name = row_get_classname;
	pdo_row_object_handlers.compare = row_compare;
}