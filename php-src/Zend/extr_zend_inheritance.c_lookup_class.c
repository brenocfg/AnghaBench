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
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ zend_class_entry ;
typedef  scalar_t__ zend_bool ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_HASHTABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG (int /*<<< orphan*/ ) ; 
 int ZEND_FETCH_CLASS_ALLOW_UNLINKED ; 
 int ZEND_FETCH_CLASS_NO_AUTOLOAD ; 
 scalar_t__ class_visible (TYPE_1__*) ; 
 int /*<<< orphan*/  delayed_autoloads ; 
 int /*<<< orphan*/  in_compilation ; 
 int /*<<< orphan*/  zend_hash_add_empty_element (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* zend_lookup_class_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ zend_string_equals_ci (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_class_entry *lookup_class(
		zend_class_entry *scope, zend_string *name, zend_bool register_unresolved) {
	zend_class_entry *ce;
	if (!CG(in_compilation)) {
		uint32_t flags = ZEND_FETCH_CLASS_ALLOW_UNLINKED | ZEND_FETCH_CLASS_NO_AUTOLOAD;
		ce = zend_lookup_class_ex(name, NULL, flags);
		if (ce) {
			return ce;
		}

		if (register_unresolved) {
			/* We'll autoload this class and process delayed variance obligations later. */
			if (!CG(delayed_autoloads)) {
				ALLOC_HASHTABLE(CG(delayed_autoloads));
				zend_hash_init(CG(delayed_autoloads), 0, NULL, NULL, 0);
			}
			zend_hash_add_empty_element(CG(delayed_autoloads), name);
		}
	} else {
		ce = zend_lookup_class_ex(name, NULL, ZEND_FETCH_CLASS_NO_AUTOLOAD);
		if (ce && class_visible(ce)) {
			return ce;
		}

		/* The current class may not be registered yet, so check for it explicitly. */
		if (zend_string_equals_ci(scope->name, name)) {
			return scope;
		}
	}

	return NULL;
}