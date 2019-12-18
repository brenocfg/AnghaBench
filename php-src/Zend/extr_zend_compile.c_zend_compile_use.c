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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int zend_bool ;
struct TYPE_7__ {scalar_t__ children; TYPE_2__** child; } ;
typedef  TYPE_1__ zend_ast_list ;
struct TYPE_8__ {scalar_t__ attr; struct TYPE_8__** child; } ;
typedef  TYPE_2__ zend_ast ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  E_COMPILE_ERROR ; 
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/ * FC (int /*<<< orphan*/ ) ; 
 scalar_t__ T_CLASS ; 
 scalar_t__ ZEND_SYMBOL_CLASS ; 
 scalar_t__ ZEND_SYMBOL_CONST ; 
 int ZSTR_LEN (int /*<<< orphan*/ *) ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_namespace ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 TYPE_1__* zend_ast_get_list (TYPE_2__*) ; 
 int /*<<< orphan*/ * zend_ast_get_str (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_check_already_in_use (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_error (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * zend_get_import_ht (scalar_t__) ; 
 scalar_t__ zend_get_unqualified_name (int /*<<< orphan*/ *,char const**,size_t*) ; 
 char* zend_get_use_type_str (scalar_t__) ; 
 int /*<<< orphan*/  zend_hash_add_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ zend_have_seen_symbol (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ zend_is_reserved_class_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_new_interned_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_str_tolower_copy (char*,char*,int) ; 
 int /*<<< orphan*/  zend_string_addref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_string_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_string_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_efree (int /*<<< orphan*/ *) ; 
 scalar_t__ zend_string_equals_literal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * zend_string_init (char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_string_tolower (int /*<<< orphan*/ *) ; 

void zend_compile_use(zend_ast *ast) /* {{{ */
{
	zend_ast_list *list = zend_ast_get_list(ast);
	uint32_t i;
	zend_string *current_ns = FC(current_namespace);
	uint32_t type = ast->attr;
	HashTable *current_import = zend_get_import_ht(type);
	zend_bool case_sensitive = type == ZEND_SYMBOL_CONST;

	for (i = 0; i < list->children; ++i) {
		zend_ast *use_ast = list->child[i];
		zend_ast *old_name_ast = use_ast->child[0];
		zend_ast *new_name_ast = use_ast->child[1];
		zend_string *old_name = zend_ast_get_str(old_name_ast);
		zend_string *new_name, *lookup_name;

		if (new_name_ast) {
			new_name = zend_string_copy(zend_ast_get_str(new_name_ast));
		} else {
			const char *unqualified_name;
			size_t unqualified_name_len;
			if (zend_get_unqualified_name(old_name, &unqualified_name, &unqualified_name_len)) {
				/* The form "use A\B" is equivalent to "use A\B as B" */
				new_name = zend_string_init(unqualified_name, unqualified_name_len, 0);
			} else {
				new_name = zend_string_copy(old_name);

				if (!current_ns) {
					if (type == T_CLASS && zend_string_equals_literal(new_name, "strict")) {
						zend_error_noreturn(E_COMPILE_ERROR,
							"You seem to be trying to use a different language...");
					}

					zend_error(E_WARNING, "The use statement with non-compound name '%s' "
						"has no effect", ZSTR_VAL(new_name));
				}
			}
		}

		if (case_sensitive) {
			lookup_name = zend_string_copy(new_name);
		} else {
			lookup_name = zend_string_tolower(new_name);
		}

		if (type == ZEND_SYMBOL_CLASS && zend_is_reserved_class_name(new_name)) {
			zend_error_noreturn(E_COMPILE_ERROR, "Cannot use %s as %s because '%s' "
				"is a special class name", ZSTR_VAL(old_name), ZSTR_VAL(new_name), ZSTR_VAL(new_name));
		}

		if (current_ns) {
			zend_string *ns_name = zend_string_alloc(ZSTR_LEN(current_ns) + 1 + ZSTR_LEN(new_name), 0);
			zend_str_tolower_copy(ZSTR_VAL(ns_name), ZSTR_VAL(current_ns), ZSTR_LEN(current_ns));
			ZSTR_VAL(ns_name)[ZSTR_LEN(current_ns)] = '\\';
			memcpy(ZSTR_VAL(ns_name) + ZSTR_LEN(current_ns) + 1, ZSTR_VAL(lookup_name), ZSTR_LEN(lookup_name) + 1);

			if (zend_have_seen_symbol(ns_name, type)) {
				zend_check_already_in_use(type, old_name, new_name, ns_name);
			}

			zend_string_efree(ns_name);
		} else if (zend_have_seen_symbol(lookup_name, type)) {
			zend_check_already_in_use(type, old_name, new_name, lookup_name);
		}

		zend_string_addref(old_name);
		old_name = zend_new_interned_string(old_name);
		if (!zend_hash_add_ptr(current_import, lookup_name, old_name)) {
			zend_error_noreturn(E_COMPILE_ERROR, "Cannot use%s %s as %s because the name "
				"is already in use", zend_get_use_type_str(type), ZSTR_VAL(old_name), ZSTR_VAL(new_name));
		}

		zend_string_release_ex(lookup_name, 0);
		zend_string_release_ex(new_name, 0);
	}
}