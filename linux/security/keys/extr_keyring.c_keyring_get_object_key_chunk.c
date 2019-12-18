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
struct key {int /*<<< orphan*/  index_key; } ;

/* Variables and functions */
 unsigned long keyring_get_key_chunk (int /*<<< orphan*/ *,int) ; 
 struct key* keyring_ptr_to_key (void const*) ; 

__attribute__((used)) static unsigned long keyring_get_object_key_chunk(const void *object, int level)
{
	const struct key *key = keyring_ptr_to_key(object);
	return keyring_get_key_chunk(&key->index_key, level);
}