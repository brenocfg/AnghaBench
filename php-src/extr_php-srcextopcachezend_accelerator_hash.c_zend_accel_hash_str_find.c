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
typedef  int /*<<< orphan*/  zend_accel_hash ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 void* zend_accel_hash_find_ex (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zend_inline_hash_func (char const*,int /*<<< orphan*/ ) ; 

void* zend_accel_hash_str_find(zend_accel_hash *accel_hash, const char *key, uint32_t key_length)
{
	return zend_accel_hash_find_ex(
		accel_hash,
		key,
		key_length,
		zend_inline_hash_func(key, key_length),
		1);
}