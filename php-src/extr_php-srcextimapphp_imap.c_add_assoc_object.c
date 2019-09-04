#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 scalar_t__ IS_OBJECT ; 
 int /*<<< orphan*/ * Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Z_OBJPROP_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/ * zend_hash_str_update (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static zval *add_assoc_object(zval *arg, char *key, zval *tmp)
{
	HashTable *symtable;

	if (Z_TYPE_P(arg) == IS_OBJECT) {
		symtable = Z_OBJPROP_P(arg);
	} else {
		symtable = Z_ARRVAL_P(arg);
	}
	return zend_hash_str_update(symtable, key, strlen(key), tmp);
}