#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object_handlers ;
typedef  int /*<<< orphan*/  zend_long ;
typedef  int /*<<< orphan*/  zend_class_entry ;
struct TYPE_6__ {int /*<<< orphan*/  get_gc; int /*<<< orphan*/  compare; int /*<<< orphan*/  get_method; int /*<<< orphan*/ * clone_obj; int /*<<< orphan*/  free_obj; int /*<<< orphan*/  dtor_obj; int /*<<< orphan*/  offset; } ;
struct TYPE_5__ {int /*<<< orphan*/  unserialize; int /*<<< orphan*/  serialize; int /*<<< orphan*/  create_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_CLASS_ENTRY (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ PDO_ATTR_AUTOCOMMIT ; 
 scalar_t__ PDO_ATTR_CASE ; 
 scalar_t__ PDO_ATTR_CLIENT_VERSION ; 
 scalar_t__ PDO_ATTR_CONNECTION_STATUS ; 
 scalar_t__ PDO_ATTR_CURSOR ; 
 scalar_t__ PDO_ATTR_CURSOR_NAME ; 
 scalar_t__ PDO_ATTR_DEFAULT_FETCH_MODE ; 
 scalar_t__ PDO_ATTR_DEFAULT_STR_PARAM ; 
 scalar_t__ PDO_ATTR_DRIVER_NAME ; 
 scalar_t__ PDO_ATTR_EMULATE_PREPARES ; 
 scalar_t__ PDO_ATTR_ERRMODE ; 
 scalar_t__ PDO_ATTR_FETCH_CATALOG_NAMES ; 
 scalar_t__ PDO_ATTR_FETCH_TABLE_NAMES ; 
 scalar_t__ PDO_ATTR_MAX_COLUMN_LEN ; 
 scalar_t__ PDO_ATTR_ORACLE_NULLS ; 
 scalar_t__ PDO_ATTR_PERSISTENT ; 
 scalar_t__ PDO_ATTR_PREFETCH ; 
 scalar_t__ PDO_ATTR_SERVER_INFO ; 
 scalar_t__ PDO_ATTR_SERVER_VERSION ; 
 scalar_t__ PDO_ATTR_STATEMENT_CLASS ; 
 scalar_t__ PDO_ATTR_STRINGIFY_FETCHES ; 
 scalar_t__ PDO_ATTR_TIMEOUT ; 
 scalar_t__ PDO_CASE_LOWER ; 
 scalar_t__ PDO_CASE_NATURAL ; 
 scalar_t__ PDO_CASE_UPPER ; 
 scalar_t__ PDO_CURSOR_FWDONLY ; 
 scalar_t__ PDO_CURSOR_SCROLL ; 
 scalar_t__ PDO_ERRMODE_EXCEPTION ; 
 scalar_t__ PDO_ERRMODE_SILENT ; 
 scalar_t__ PDO_ERRMODE_WARNING ; 
 int /*<<< orphan*/  PDO_ERR_NONE ; 
 scalar_t__ PDO_FETCH_ASSOC ; 
 scalar_t__ PDO_FETCH_BOTH ; 
 scalar_t__ PDO_FETCH_BOUND ; 
 scalar_t__ PDO_FETCH_CLASS ; 
 scalar_t__ PDO_FETCH_CLASSTYPE ; 
 scalar_t__ PDO_FETCH_COLUMN ; 
 scalar_t__ PDO_FETCH_FUNC ; 
 scalar_t__ PDO_FETCH_GROUP ; 
 scalar_t__ PDO_FETCH_INTO ; 
 scalar_t__ PDO_FETCH_KEY_PAIR ; 
 scalar_t__ PDO_FETCH_LAZY ; 
 scalar_t__ PDO_FETCH_NAMED ; 
 scalar_t__ PDO_FETCH_NUM ; 
 scalar_t__ PDO_FETCH_OBJ ; 
 scalar_t__ PDO_FETCH_ORI_ABS ; 
 scalar_t__ PDO_FETCH_ORI_FIRST ; 
 scalar_t__ PDO_FETCH_ORI_LAST ; 
 scalar_t__ PDO_FETCH_ORI_NEXT ; 
 scalar_t__ PDO_FETCH_ORI_PRIOR ; 
 scalar_t__ PDO_FETCH_ORI_REL ; 
 scalar_t__ PDO_FETCH_PROPS_LATE ; 
 scalar_t__ PDO_FETCH_SERIALIZE ; 
 scalar_t__ PDO_FETCH_UNIQUE ; 
 scalar_t__ PDO_NULL_EMPTY_STRING ; 
 scalar_t__ PDO_NULL_NATURAL ; 
 scalar_t__ PDO_NULL_TO_STRING ; 
 scalar_t__ PDO_PARAM_BOOL ; 
 scalar_t__ PDO_PARAM_EVT_ALLOC ; 
 scalar_t__ PDO_PARAM_EVT_EXEC_POST ; 
 scalar_t__ PDO_PARAM_EVT_EXEC_PRE ; 
 scalar_t__ PDO_PARAM_EVT_FETCH_POST ; 
 scalar_t__ PDO_PARAM_EVT_FETCH_PRE ; 
 scalar_t__ PDO_PARAM_EVT_FREE ; 
 scalar_t__ PDO_PARAM_EVT_NORMALIZE ; 
 scalar_t__ PDO_PARAM_INPUT_OUTPUT ; 
 scalar_t__ PDO_PARAM_INT ; 
 scalar_t__ PDO_PARAM_LOB ; 
 scalar_t__ PDO_PARAM_NULL ; 
 scalar_t__ PDO_PARAM_STMT ; 
 scalar_t__ PDO_PARAM_STR ; 
 scalar_t__ PDO_PARAM_STR_CHAR ; 
 scalar_t__ PDO_PARAM_STR_NATL ; 
 int /*<<< orphan*/  REGISTER_PDO_CLASS_CONST_LONG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGISTER_PDO_CLASS_CONST_STRING (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XtOffsetOf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbh_compare ; 
 int /*<<< orphan*/  dbh_get_gc ; 
 int /*<<< orphan*/  dbh_method_get ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* pdo_dbh_ce ; 
 int /*<<< orphan*/  pdo_dbh_free_storage ; 
 int /*<<< orphan*/  pdo_dbh_functions ; 
 int /*<<< orphan*/  pdo_dbh_new ; 
 TYPE_2__ pdo_dbh_object_handlers ; 
 int /*<<< orphan*/  pdo_dbh_object_t ; 
 int /*<<< orphan*/  std ; 
 int /*<<< orphan*/  std_object_handlers ; 
 int /*<<< orphan*/  zend_class_serialize_deny ; 
 int /*<<< orphan*/  zend_class_unserialize_deny ; 
 int /*<<< orphan*/  zend_objects_destroy_object ; 
 TYPE_1__* zend_register_internal_class (int /*<<< orphan*/ *) ; 

void pdo_dbh_init(void)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "PDO", pdo_dbh_functions);
	pdo_dbh_ce = zend_register_internal_class(&ce);
	pdo_dbh_ce->create_object = pdo_dbh_new;
	pdo_dbh_ce->serialize = zend_class_serialize_deny;
	pdo_dbh_ce->unserialize = zend_class_unserialize_deny;

	memcpy(&pdo_dbh_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
	pdo_dbh_object_handlers.offset = XtOffsetOf(pdo_dbh_object_t, std);
	pdo_dbh_object_handlers.dtor_obj = zend_objects_destroy_object;
	pdo_dbh_object_handlers.free_obj = pdo_dbh_free_storage;
	pdo_dbh_object_handlers.clone_obj = NULL;
	pdo_dbh_object_handlers.get_method = dbh_method_get;
	pdo_dbh_object_handlers.compare = dbh_compare;
	pdo_dbh_object_handlers.get_gc = dbh_get_gc;

	REGISTER_PDO_CLASS_CONST_LONG("PARAM_BOOL", (zend_long)PDO_PARAM_BOOL);
	REGISTER_PDO_CLASS_CONST_LONG("PARAM_NULL", (zend_long)PDO_PARAM_NULL);
	REGISTER_PDO_CLASS_CONST_LONG("PARAM_INT",  (zend_long)PDO_PARAM_INT);
	REGISTER_PDO_CLASS_CONST_LONG("PARAM_STR",  (zend_long)PDO_PARAM_STR);
	REGISTER_PDO_CLASS_CONST_LONG("PARAM_LOB",  (zend_long)PDO_PARAM_LOB);
	REGISTER_PDO_CLASS_CONST_LONG("PARAM_STMT", (zend_long)PDO_PARAM_STMT);
	REGISTER_PDO_CLASS_CONST_LONG("PARAM_INPUT_OUTPUT", (zend_long)PDO_PARAM_INPUT_OUTPUT);
	REGISTER_PDO_CLASS_CONST_LONG("PARAM_STR_NATL", (zend_long)PDO_PARAM_STR_NATL);
	REGISTER_PDO_CLASS_CONST_LONG("PARAM_STR_CHAR", (zend_long)PDO_PARAM_STR_CHAR);


	REGISTER_PDO_CLASS_CONST_LONG("PARAM_EVT_ALLOC",		(zend_long)PDO_PARAM_EVT_ALLOC);
	REGISTER_PDO_CLASS_CONST_LONG("PARAM_EVT_FREE",			(zend_long)PDO_PARAM_EVT_FREE);
	REGISTER_PDO_CLASS_CONST_LONG("PARAM_EVT_EXEC_PRE",		(zend_long)PDO_PARAM_EVT_EXEC_PRE);
	REGISTER_PDO_CLASS_CONST_LONG("PARAM_EVT_EXEC_POST",	(zend_long)PDO_PARAM_EVT_EXEC_POST);
	REGISTER_PDO_CLASS_CONST_LONG("PARAM_EVT_FETCH_PRE",	(zend_long)PDO_PARAM_EVT_FETCH_PRE);
	REGISTER_PDO_CLASS_CONST_LONG("PARAM_EVT_FETCH_POST",	(zend_long)PDO_PARAM_EVT_FETCH_POST);
	REGISTER_PDO_CLASS_CONST_LONG("PARAM_EVT_NORMALIZE",	(zend_long)PDO_PARAM_EVT_NORMALIZE);

	REGISTER_PDO_CLASS_CONST_LONG("FETCH_LAZY", (zend_long)PDO_FETCH_LAZY);
	REGISTER_PDO_CLASS_CONST_LONG("FETCH_ASSOC", (zend_long)PDO_FETCH_ASSOC);
	REGISTER_PDO_CLASS_CONST_LONG("FETCH_NUM",  (zend_long)PDO_FETCH_NUM);
	REGISTER_PDO_CLASS_CONST_LONG("FETCH_BOTH", (zend_long)PDO_FETCH_BOTH);
	REGISTER_PDO_CLASS_CONST_LONG("FETCH_OBJ",  (zend_long)PDO_FETCH_OBJ);
	REGISTER_PDO_CLASS_CONST_LONG("FETCH_BOUND", (zend_long)PDO_FETCH_BOUND);
	REGISTER_PDO_CLASS_CONST_LONG("FETCH_COLUMN", (zend_long)PDO_FETCH_COLUMN);
	REGISTER_PDO_CLASS_CONST_LONG("FETCH_CLASS", (zend_long)PDO_FETCH_CLASS);
	REGISTER_PDO_CLASS_CONST_LONG("FETCH_INTO", (zend_long)PDO_FETCH_INTO);
	REGISTER_PDO_CLASS_CONST_LONG("FETCH_FUNC", (zend_long)PDO_FETCH_FUNC);
	REGISTER_PDO_CLASS_CONST_LONG("FETCH_GROUP", (zend_long)PDO_FETCH_GROUP);
	REGISTER_PDO_CLASS_CONST_LONG("FETCH_UNIQUE", (zend_long)PDO_FETCH_UNIQUE);
	REGISTER_PDO_CLASS_CONST_LONG("FETCH_KEY_PAIR", (zend_long)PDO_FETCH_KEY_PAIR);
	REGISTER_PDO_CLASS_CONST_LONG("FETCH_CLASSTYPE", (zend_long)PDO_FETCH_CLASSTYPE);

	REGISTER_PDO_CLASS_CONST_LONG("FETCH_SERIALIZE",(zend_long)PDO_FETCH_SERIALIZE);
	REGISTER_PDO_CLASS_CONST_LONG("FETCH_PROPS_LATE", (zend_long)PDO_FETCH_PROPS_LATE);
	REGISTER_PDO_CLASS_CONST_LONG("FETCH_NAMED", (zend_long)PDO_FETCH_NAMED);

	REGISTER_PDO_CLASS_CONST_LONG("ATTR_AUTOCOMMIT",	(zend_long)PDO_ATTR_AUTOCOMMIT);
	REGISTER_PDO_CLASS_CONST_LONG("ATTR_PREFETCH",		(zend_long)PDO_ATTR_PREFETCH);
	REGISTER_PDO_CLASS_CONST_LONG("ATTR_TIMEOUT", 		(zend_long)PDO_ATTR_TIMEOUT);
	REGISTER_PDO_CLASS_CONST_LONG("ATTR_ERRMODE", 		(zend_long)PDO_ATTR_ERRMODE);
	REGISTER_PDO_CLASS_CONST_LONG("ATTR_SERVER_VERSION",	(zend_long)PDO_ATTR_SERVER_VERSION);
	REGISTER_PDO_CLASS_CONST_LONG("ATTR_CLIENT_VERSION", 	(zend_long)PDO_ATTR_CLIENT_VERSION);
	REGISTER_PDO_CLASS_CONST_LONG("ATTR_SERVER_INFO",		(zend_long)PDO_ATTR_SERVER_INFO);
	REGISTER_PDO_CLASS_CONST_LONG("ATTR_CONNECTION_STATUS", 	(zend_long)PDO_ATTR_CONNECTION_STATUS);
	REGISTER_PDO_CLASS_CONST_LONG("ATTR_CASE",		 	(zend_long)PDO_ATTR_CASE);
	REGISTER_PDO_CLASS_CONST_LONG("ATTR_CURSOR_NAME", 	(zend_long)PDO_ATTR_CURSOR_NAME);
	REGISTER_PDO_CLASS_CONST_LONG("ATTR_CURSOR",	 	(zend_long)PDO_ATTR_CURSOR);
	REGISTER_PDO_CLASS_CONST_LONG("ATTR_ORACLE_NULLS",	(zend_long)PDO_ATTR_ORACLE_NULLS);
	REGISTER_PDO_CLASS_CONST_LONG("ATTR_PERSISTENT",	(zend_long)PDO_ATTR_PERSISTENT);
	REGISTER_PDO_CLASS_CONST_LONG("ATTR_STATEMENT_CLASS",		(zend_long)PDO_ATTR_STATEMENT_CLASS);
	REGISTER_PDO_CLASS_CONST_LONG("ATTR_FETCH_TABLE_NAMES",		(zend_long)PDO_ATTR_FETCH_TABLE_NAMES);
	REGISTER_PDO_CLASS_CONST_LONG("ATTR_FETCH_CATALOG_NAMES",		(zend_long)PDO_ATTR_FETCH_CATALOG_NAMES);
	REGISTER_PDO_CLASS_CONST_LONG("ATTR_DRIVER_NAME",		(zend_long)PDO_ATTR_DRIVER_NAME);
	REGISTER_PDO_CLASS_CONST_LONG("ATTR_STRINGIFY_FETCHES", (zend_long)PDO_ATTR_STRINGIFY_FETCHES);
	REGISTER_PDO_CLASS_CONST_LONG("ATTR_MAX_COLUMN_LEN", (zend_long)PDO_ATTR_MAX_COLUMN_LEN);
	REGISTER_PDO_CLASS_CONST_LONG("ATTR_EMULATE_PREPARES", (zend_long)PDO_ATTR_EMULATE_PREPARES);
	REGISTER_PDO_CLASS_CONST_LONG("ATTR_DEFAULT_FETCH_MODE", (zend_long)PDO_ATTR_DEFAULT_FETCH_MODE);
	REGISTER_PDO_CLASS_CONST_LONG("ATTR_DEFAULT_STR_PARAM", (zend_long)PDO_ATTR_DEFAULT_STR_PARAM);

	REGISTER_PDO_CLASS_CONST_LONG("ERRMODE_SILENT",	(zend_long)PDO_ERRMODE_SILENT);
	REGISTER_PDO_CLASS_CONST_LONG("ERRMODE_WARNING",	(zend_long)PDO_ERRMODE_WARNING);
	REGISTER_PDO_CLASS_CONST_LONG("ERRMODE_EXCEPTION",	(zend_long)PDO_ERRMODE_EXCEPTION);

	REGISTER_PDO_CLASS_CONST_LONG("CASE_NATURAL",	(zend_long)PDO_CASE_NATURAL);
	REGISTER_PDO_CLASS_CONST_LONG("CASE_LOWER",	(zend_long)PDO_CASE_LOWER);
	REGISTER_PDO_CLASS_CONST_LONG("CASE_UPPER",	(zend_long)PDO_CASE_UPPER);

	REGISTER_PDO_CLASS_CONST_LONG("NULL_NATURAL",	(zend_long)PDO_NULL_NATURAL);
	REGISTER_PDO_CLASS_CONST_LONG("NULL_EMPTY_STRING",	(zend_long)PDO_NULL_EMPTY_STRING);
	REGISTER_PDO_CLASS_CONST_LONG("NULL_TO_STRING",	(zend_long)PDO_NULL_TO_STRING);

	REGISTER_PDO_CLASS_CONST_STRING("ERR_NONE",	PDO_ERR_NONE);

	REGISTER_PDO_CLASS_CONST_LONG("FETCH_ORI_NEXT", (zend_long)PDO_FETCH_ORI_NEXT);
	REGISTER_PDO_CLASS_CONST_LONG("FETCH_ORI_PRIOR", (zend_long)PDO_FETCH_ORI_PRIOR);
	REGISTER_PDO_CLASS_CONST_LONG("FETCH_ORI_FIRST", (zend_long)PDO_FETCH_ORI_FIRST);
	REGISTER_PDO_CLASS_CONST_LONG("FETCH_ORI_LAST", (zend_long)PDO_FETCH_ORI_LAST);
	REGISTER_PDO_CLASS_CONST_LONG("FETCH_ORI_ABS", (zend_long)PDO_FETCH_ORI_ABS);
	REGISTER_PDO_CLASS_CONST_LONG("FETCH_ORI_REL", (zend_long)PDO_FETCH_ORI_REL);

	REGISTER_PDO_CLASS_CONST_LONG("CURSOR_FWDONLY", (zend_long)PDO_CURSOR_FWDONLY);
	REGISTER_PDO_CLASS_CONST_LONG("CURSOR_SCROLL", (zend_long)PDO_CURSOR_SCROLL);
}