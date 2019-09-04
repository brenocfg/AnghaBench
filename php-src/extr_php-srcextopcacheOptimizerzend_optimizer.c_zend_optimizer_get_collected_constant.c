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
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_hash_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int zend_optimizer_get_collected_constant(HashTable *constants, zval *name, zval* value)
{
	zval *val;

	if ((val = zend_hash_find(constants, Z_STR_P(name))) != NULL) {
		ZVAL_COPY(value, val);
		return 1;
	}
	return 0;
}