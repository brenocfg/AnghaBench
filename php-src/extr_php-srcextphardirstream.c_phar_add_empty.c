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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int SUCCESS ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_str_update (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int phar_add_empty(HashTable *ht, char *arKey, uint32_t nKeyLength)  /* {{{ */
{
	zval dummy;

	ZVAL_NULL(&dummy);
	zend_hash_str_update(ht, arKey, nKeyLength, &dummy);
	return SUCCESS;
}