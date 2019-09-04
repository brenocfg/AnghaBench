#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  TYPE_1__* xmlNodePtr ;
struct TYPE_4__ {struct TYPE_4__* next; scalar_t__ name; } ;

/* Variables and functions */
 scalar_t__ IS_ARRAY ; 
 scalar_t__ IS_STRING ; 
 int /*<<< orphan*/  XSD_ANYXML ; 
 int /*<<< orphan*/  ZVAL_COPY_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 char* Z_STRVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_TRY_DELREF (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_assoc_zval (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_next_index_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  concat_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_conversion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_zval_property (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  master_to_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  set_zval_property (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/ * zend_hash_str_find (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void model_to_zval_any(zval *ret, xmlNodePtr node)
{
	zval rv, arr, val, keepVal;
	zval* any = NULL;
	char* name = NULL;

	while (node != NULL) {
		if (get_zval_property(ret, (char*)node->name, &rv) == NULL) {

			ZVAL_NULL(&val);
			master_to_zval(&val, get_conversion(XSD_ANYXML), node);

			if (any && Z_TYPE_P(any) != IS_ARRAY) {
				/* Convert into array */
				array_init(&arr);
				if (name) {
					add_assoc_zval(&arr, name, any);
				} else {
					add_next_index_zval(&arr, any);
				}
				any = &arr;
			}

			if (Z_TYPE(val) == IS_STRING && *Z_STRVAL(val) == '<') {
				name = NULL;
				while (node->next != NULL) {
					zval val2;

					ZVAL_NULL(&val2);
					master_to_zval(&val2, get_conversion(XSD_ANYXML), node->next);
					if (Z_TYPE(val2) != IS_STRING ||  *Z_STRVAL(val) != '<') {
						Z_TRY_DELREF(val2);
						break;
					}
					concat_function(&val, &val, &val2);
					zval_ptr_dtor(&val2);
					node = node->next;
				}
			} else {
				name = (char*)node->name;
			}

			if (any == NULL) {
				if (name) {
					/* Convert into array */
					array_init(&arr);
					add_assoc_zval(&arr, name, &val);
					any = &arr;
					name = NULL;
				} else {
					ZVAL_COPY_VALUE(&keepVal, &val);
					any = &keepVal;
				}
			} else {
				/* Add array element */
				if (name) {
					zval *el;
					if ((el = zend_hash_str_find(Z_ARRVAL_P(any), name, strlen(name))) != NULL) {
						if (Z_TYPE_P(el) != IS_ARRAY) {
							/* Convert into array */
							array_init(&arr);
							add_next_index_zval(&arr, el);
							el = &arr;
						}
						add_next_index_zval(el, &val);
					} else {
						add_assoc_zval(any, name, &val);
					}
				} else {
					add_next_index_zval(any, &val);
				}
				name = NULL;
			}
		}
		node = node->next;
	}
	if (any) {
		set_zval_property(ret, name ? name : "any", any);
	}
}