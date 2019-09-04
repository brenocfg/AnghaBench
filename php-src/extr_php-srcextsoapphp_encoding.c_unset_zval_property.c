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

/* Variables and functions */
 scalar_t__ IS_ARRAY ; 
 scalar_t__ IS_OBJECT ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_OBJCE_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  zend_hash_str_del (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_unset_property (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unset_zval_property(zval* object, char* name)
{
	if (Z_TYPE_P(object) == IS_OBJECT) {
		zend_unset_property(Z_OBJCE_P(object), object, name, strlen(name));
	} else if (Z_TYPE_P(object) == IS_ARRAY) {
		zend_hash_str_del(Z_ARRVAL_P(object), name, strlen(name));
	}
}