#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_6__ {struct TYPE_6__* parent; int /*<<< orphan*/ * str; int /*<<< orphan*/  flags; struct TYPE_6__* child; } ;
typedef  TYPE_1__ phpdbg_watch_element ;
typedef  int /*<<< orphan*/  Bucket ;

/* Variables and functions */
 int FAILURE ; 
 scalar_t__ IS_ARRAY ; 
 scalar_t__ IS_OBJECT ; 
 int /*<<< orphan*/  PHPDBG_WATCH_IMPLICIT ; 
 int /*<<< orphan*/  PHPDBG_WATCH_SIMPLE ; 
 int SUCCESS ; 
 scalar_t__ ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_DEREF (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 TYPE_1__* ecalloc (int,int) ; 
 int /*<<< orphan*/  phpdbg_add_bucket_watch_element (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  phpdbg_add_ht_watch_element (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * strpprintf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_string_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int phpdbg_create_array_watchpoint(zval *zv, phpdbg_watch_element *element) {
	phpdbg_watch_element *new;
	zend_string *str;
	zval *orig_zv = zv;

	ZVAL_DEREF(zv);
	if (Z_TYPE_P(zv) != IS_ARRAY && Z_TYPE_P(zv) != IS_OBJECT) {
		return FAILURE;
	}

	new = ecalloc(1, sizeof(phpdbg_watch_element));

	str = strpprintf(0, "%.*s[]", (int) ZSTR_LEN(element->str), ZSTR_VAL(element->str));
	zend_string_release(element->str);
	element->str = str;
	element->flags = PHPDBG_WATCH_IMPLICIT;
	phpdbg_add_bucket_watch_element((Bucket *) orig_zv, element);
	element->child = new;

	new->flags = PHPDBG_WATCH_SIMPLE;
	new->str = zend_string_copy(str);
	new->parent = element;
	phpdbg_add_ht_watch_element(zv, new);
	return SUCCESS;
}