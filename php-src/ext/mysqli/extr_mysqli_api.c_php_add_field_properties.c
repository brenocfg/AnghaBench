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
struct TYPE_3__ {char* name; char* org_name; char* table; char* org_table; char* def; char* db; int /*<<< orphan*/  decimals; int /*<<< orphan*/  type; int /*<<< orphan*/  flags; int /*<<< orphan*/  charsetnr; int /*<<< orphan*/  length; int /*<<< orphan*/  max_length; int /*<<< orphan*/  db_length; int /*<<< orphan*/  def_length; int /*<<< orphan*/  org_table_length; int /*<<< orphan*/  table_length; int /*<<< orphan*/  org_name_length; int /*<<< orphan*/  name_length; int /*<<< orphan*/  sname; } ;
typedef  TYPE_1__ MYSQL_FIELD ;

/* Variables and functions */
 int /*<<< orphan*/  add_property_long (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_property_str (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_property_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  add_property_stringl (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_copy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void php_add_field_properties(zval *value, const MYSQL_FIELD *field)
{
#ifdef MYSQLI_USE_MYSQLND
	add_property_str(value, "name", zend_string_copy(field->sname));
#else
	add_property_stringl(value, "name",(field->name ? field->name : ""), field->name_length);
#endif

	add_property_stringl(value, "orgname", (field->org_name ? field->org_name : ""), field->org_name_length);
	add_property_stringl(value, "table", (field->table ? field->table : ""), field->table_length);
	add_property_stringl(value, "orgtable", (field->org_table ? field->org_table : ""), field->org_table_length);
	add_property_stringl(value, "def", (field->def ? field->def : ""), field->def_length);
	add_property_stringl(value, "db", (field->db ? field->db : ""), field->db_length);

	/* FIXME: manually set the catalog to "def" due to bug in
	 * libmysqlclient which does not initialize field->catalog
	 * and in addition, the catalog is always be "def"
	 */
	add_property_string(value, "catalog", "def");

	add_property_long(value, "max_length", field->max_length);
	add_property_long(value, "length", field->length);
	add_property_long(value, "charsetnr", field->charsetnr);
	add_property_long(value, "flags", field->flags);
	add_property_long(value, "type", field->type);
	add_property_long(value, "decimals", field->decimals);
}