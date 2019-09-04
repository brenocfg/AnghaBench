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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_accel_hash_entry ;
typedef  int /*<<< orphan*/  zend_accel_hash ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 scalar_t__ zend_accel_hash_find_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_hash_val (int /*<<< orphan*/ *) ; 

zend_accel_hash_entry* zend_accel_hash_find_entry(zend_accel_hash *accel_hash, zend_string *key)
{
	return (zend_accel_hash_entry *)zend_accel_hash_find_ex(
		accel_hash,
		ZSTR_VAL(key),
		ZSTR_LEN(key),
		zend_string_hash_val(key),
		0);
}