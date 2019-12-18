#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_4__ {int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ zend_ast ;
struct TYPE_5__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
#define  IS_ARRAY 138 
#define  IS_CONSTANT_AST 137 
#define  IS_DOUBLE 136 
#define  IS_FALSE 135 
#define  IS_LONG 134 
#define  IS_NULL 133 
#define  IS_OBJECT 132 
#define  IS_RESOURCE 131 
#define  IS_STRING 130 
#define  IS_TRUE 129 
#define  IS_UNDEF 128 
 int /*<<< orphan*/  ZEND_AST_CONSTANT ; 
 int /*<<< orphan*/  ZEND_AST_CONSTANT_CLASS ; 
 char* ZEND_LONG_FMT ; 
 int ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ARR_P (int /*<<< orphan*/ *) ; 
 TYPE_1__* Z_ASTVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_DVAL_P (int /*<<< orphan*/ *) ; 
 int Z_LVAL_P (int /*<<< orphan*/ *) ; 
 TYPE_2__* Z_OBJCE_P (int /*<<< orphan*/ *) ; 
 int Z_RES_HANDLE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STR_P (int /*<<< orphan*/ *) ; 
 int Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* emalloc (int /*<<< orphan*/ ) ; 
 char* estrdup (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/ * php_addcslashes (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  spprintf (char**,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  strchr (char*,char) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  zend_finite (int /*<<< orphan*/ ) ; 
 int zend_hash_num_elements (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ *) ; 

char *phpdbg_short_zval_print(zval *zv, int maxlen) /* {{{ */
{
	char *decode = NULL;

	switch (Z_TYPE_P(zv)) {
		case IS_UNDEF:
			decode = estrdup("");
			break;
		case IS_NULL:
			decode = estrdup("null");
			break;
		case IS_FALSE:
			decode = estrdup("false");
			break;
		case IS_TRUE:
			decode = estrdup("true");
			break;
		case IS_LONG:
			spprintf(&decode, 0, ZEND_LONG_FMT, Z_LVAL_P(zv));
			break;
		case IS_DOUBLE:
			spprintf(&decode, 0, "%.*G", 14, Z_DVAL_P(zv));

			/* Make sure it looks like a float */
			if (zend_finite(Z_DVAL_P(zv)) && !strchr(decode, '.')) {
				size_t len = strlen(decode);
				char *decode2 = emalloc(len + strlen(".0") + 1);
				memcpy(decode2, decode, len);
				decode2[len] = '.';
				decode2[len+1] = '0';
				decode2[len+2] = '\0';
				efree(decode);
				decode = decode2;
			}
			break;
		case IS_STRING: {
			int i;
			zend_string *str = php_addcslashes(Z_STR_P(zv), "\\\"\n\t\0", 5);
			for (i = 0; i < ZSTR_LEN(str); i++) {
				if (ZSTR_VAL(str)[i] < 32) {
					ZSTR_VAL(str)[i] = ' ';
				}
			}
			spprintf(&decode, 0, "\"%.*s\"%c",
				ZSTR_LEN(str) <= maxlen - 2 ? (int) ZSTR_LEN(str) : (maxlen - 3),
				ZSTR_VAL(str), ZSTR_LEN(str) <= maxlen - 2 ? 0 : '+');
			zend_string_release(str);
			} break;
		case IS_RESOURCE:
			spprintf(&decode, 0, "Rsrc #%d", Z_RES_HANDLE_P(zv));
			break;
		case IS_ARRAY:
			spprintf(&decode, 0, "array(%d)", zend_hash_num_elements(Z_ARR_P(zv)));
			break;
		case IS_OBJECT: {
			zend_string *str = Z_OBJCE_P(zv)->name;
			spprintf(&decode, 0, "%.*s%c",
				ZSTR_LEN(str) <= maxlen ? (int) ZSTR_LEN(str) : maxlen - 1,
				ZSTR_VAL(str), ZSTR_LEN(str) <= maxlen ? 0 : '+');
			break;
		}
		case IS_CONSTANT_AST: {
			zend_ast *ast = Z_ASTVAL_P(zv);

			if (ast->kind == ZEND_AST_CONSTANT
			 || ast->kind == ZEND_AST_CONSTANT_CLASS) {
				decode = estrdup("<constant>");
			} else {
				decode = estrdup("<ast>");
			}
			break;
		}
		default:
			spprintf(&decode, 0, "unknown type: %d", Z_TYPE_P(zv));
			break;
	}

	return decode;
}