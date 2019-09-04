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
typedef  int /*<<< orphan*/  zend_string ;
struct php_sqlite3_bound_param {int param_number; int /*<<< orphan*/ * name; } ;
struct TYPE_3__ {int /*<<< orphan*/  stmt; int /*<<< orphan*/ * bound_params; } ;
typedef  TYPE_1__ php_sqlite3_stmt ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_HASHTABLE (int /*<<< orphan*/ *) ; 
 scalar_t__ ZSTR_LEN (int /*<<< orphan*/ *) ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (char*,char*,scalar_t__) ; 
 int sqlite3_bind_parameter_index (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sqlite3_param_dtor ; 
 int /*<<< orphan*/  zend_hash_index_del (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zend_hash_index_update_mem (int /*<<< orphan*/ *,int,struct php_sqlite3_bound_param*,int) ; 
 int /*<<< orphan*/  zend_hash_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_update_mem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct php_sqlite3_bound_param*,int) ; 
 int /*<<< orphan*/ * zend_string_alloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_string_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int register_bound_parameter_to_sqlite(struct php_sqlite3_bound_param *param, php_sqlite3_stmt *stmt) /* {{{ */
{
	HashTable *hash;
	hash = stmt->bound_params;

	if (!hash) {
		ALLOC_HASHTABLE(hash);
		zend_hash_init(hash, 13, NULL, sqlite3_param_dtor, 0);
		stmt->bound_params = hash;
	}

	/* We need a : prefix to resolve a name to a parameter number */
	if (param->name) {
		if (ZSTR_VAL(param->name)[0] != ':' && ZSTR_VAL(param->name)[0] != '@') {
			/* pre-increment for character + 1 for null */
			zend_string *temp = zend_string_alloc(ZSTR_LEN(param->name) + 1, 0);
			ZSTR_VAL(temp)[0] = ':';
			memmove(ZSTR_VAL(temp) + 1, ZSTR_VAL(param->name), ZSTR_LEN(param->name) + 1);
			param->name = temp;
		} else {
			param->name = zend_string_copy(param->name);
		}
		/* do lookup*/
		param->param_number = sqlite3_bind_parameter_index(stmt->stmt, ZSTR_VAL(param->name));
	}

	if (param->param_number < 1) {
		if (param->name) {
			zend_string_release_ex(param->name, 0);
		}
		return 0;
	}

	if (param->param_number >= 1) {
		zend_hash_index_del(hash, param->param_number);
	}

	if (param->name) {
		zend_hash_update_mem(hash, param->name, param, sizeof(struct php_sqlite3_bound_param));
	} else {
		zend_hash_index_update_mem(hash, param->param_number, param, sizeof(struct php_sqlite3_bound_param));
	}

	return 1;
}