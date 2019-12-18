#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_12__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_4__ zend_module_entry ;
struct TYPE_10__ {TYPE_1__* module; } ;
struct TYPE_11__ {TYPE_2__ internal; } ;
struct TYPE_13__ {scalar_t__ type; int /*<<< orphan*/ * name; TYPE_3__ info; } ;
typedef  TYPE_5__ zend_class_entry ;
typedef  scalar_t__ zend_bool ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ ZEND_INTERNAL_CLASS ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_next_index_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_update (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_reflection_class_factory (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_equals_ci (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_extension_class(zend_class_entry *ce, zend_string *key, zval *class_array, zend_module_entry *module, zend_bool add_reflection_class)
{
	if (ce->type == ZEND_INTERNAL_CLASS && ce->info.internal.module && !strcasecmp(ce->info.internal.module->name, module->name)) {
		zend_string *name;

		if (!zend_string_equals_ci(ce->name, key)) {
			/* This is a class alias, use alias name */
			name = key;
		} else {
			/* Use class name */
			name = ce->name;
		}
		if (add_reflection_class) {
			zval zclass;
			zend_reflection_class_factory(ce, &zclass);
			zend_hash_update(Z_ARRVAL_P(class_array), name, &zclass);
		} else {
			add_next_index_str(class_array, zend_string_copy(name));
		}
	}
}