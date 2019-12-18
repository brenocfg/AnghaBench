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
struct key_preparsed_payload {int dummy; } ;
struct key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSCRYPT_MAX_KEY_SIZE ; 
 int key_payload_reserve (struct key*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fscrypt_user_key_instantiate(struct key *key,
					struct key_preparsed_payload *prep)
{
	/*
	 * We just charge FSCRYPT_MAX_KEY_SIZE bytes to the user's key quota for
	 * each key, regardless of the exact key size.  The amount of memory
	 * actually used is greater than the size of the raw key anyway.
	 */
	return key_payload_reserve(key, FSCRYPT_MAX_KEY_SIZE);
}