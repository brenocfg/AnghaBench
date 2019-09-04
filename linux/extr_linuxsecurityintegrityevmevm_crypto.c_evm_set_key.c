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

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  EVM_INIT_HMAC ; 
 int /*<<< orphan*/  EVM_SET_KEY_BUSY ; 
 size_t MAX_KEY_SIZE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evm_initialized ; 
 int /*<<< orphan*/  evm_set_key_flags ; 
 int /*<<< orphan*/  evmkey ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int evm_set_key(void *key, size_t keylen)
{
	int rc;

	rc = -EBUSY;
	if (test_and_set_bit(EVM_SET_KEY_BUSY, &evm_set_key_flags))
		goto busy;
	rc = -EINVAL;
	if (keylen > MAX_KEY_SIZE)
		goto inval;
	memcpy(evmkey, key, keylen);
	evm_initialized |= EVM_INIT_HMAC;
	pr_info("key initialized\n");
	return 0;
inval:
	clear_bit(EVM_SET_KEY_BUSY, &evm_set_key_flags);
busy:
	pr_err("key initialization failed\n");
	return rc;
}