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
typedef  char zval ;
typedef  int zend_bool ;
struct TYPE_7__ {char zv; int /*<<< orphan*/  ht; } ;
struct TYPE_8__ {int flags; int /*<<< orphan*/ * parent_container; TYPE_1__ backup; int /*<<< orphan*/  str; struct TYPE_8__* child; int /*<<< orphan*/  name_in_parent; } ;
typedef  TYPE_2__ phpdbg_watch_element ;
typedef  int /*<<< orphan*/  HashTable ;
typedef  int /*<<< orphan*/  Bucket ;

/* Variables and functions */
 int /*<<< orphan*/ * HT_FROM_ZVP (char*) ; 
 int HT_WATCH_OFFSET ; 
 scalar_t__ IS_INDIRECT ; 
 int PHPDBG_WATCH_ARRAY ; 
 int PHPDBG_WATCH_IMPLICIT ; 
 int PHPDBG_WATCH_OBJECT ; 
 int /*<<< orphan*/  WATCH_ON_HASHTABLE ; 
 int /*<<< orphan*/  WATCH_ON_ZVAL ; 
 char* Z_INDIRECT_P (char*) ; 
 scalar_t__ Z_ISREF_P (char*) ; 
 char* Z_REFVAL_P (char*) ; 
 scalar_t__ Z_TYPE_P (char*) ; 
 int /*<<< orphan*/  phpdbg_add_bucket_watch_element (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  phpdbg_add_ht_watch_element (char*,TYPE_2__*) ; 
 scalar_t__ phpdbg_check_watch_diff (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  phpdbg_print_watch_diff (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  phpdbg_watch_parent_ht (TYPE_2__*) ; 
 char* zend_symtable_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

zend_bool phpdbg_try_readding_watch_element(zval *parent, phpdbg_watch_element *element) {
	zval *zv;
	HashTable *ht = HT_FROM_ZVP(parent);

	if (!ht) {
		return 0;
	} else if (element->flags & (PHPDBG_WATCH_ARRAY | PHPDBG_WATCH_OBJECT)) {
		char *htPtr = ((char *) ht) + HT_WATCH_OFFSET;
		char *oldPtr = ((char *) &element->backup.ht) + HT_WATCH_OFFSET;
		if (phpdbg_check_watch_diff(WATCH_ON_HASHTABLE, oldPtr, htPtr)) {
			phpdbg_print_watch_diff(WATCH_ON_HASHTABLE, element->str, oldPtr, htPtr);
		}

		phpdbg_add_ht_watch_element(parent, element);
	} else if ((zv = zend_symtable_find(ht, element->name_in_parent))) {
		if (element->flags & PHPDBG_WATCH_IMPLICIT) {
			zval *next = zv;

			while (Z_TYPE_P(next) == IS_INDIRECT) {
				next = Z_INDIRECT_P(next);
			}
			if (Z_ISREF_P(next)) {
				next = Z_REFVAL_P(next);
			}

			if (!phpdbg_try_readding_watch_element(next, element->child)) {
				return 0;
			}
		} else if (phpdbg_check_watch_diff(WATCH_ON_ZVAL, &element->backup.zv, zv)) {
			phpdbg_print_watch_diff(WATCH_ON_ZVAL, element->str, &element->backup.zv, zv);
		}

		element->parent_container = ht;
		phpdbg_add_bucket_watch_element((Bucket *) zv, element);
		phpdbg_watch_parent_ht(element);
	} else {
		return 0;
	}

	return 1;
}