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
typedef  int /*<<< orphan*/  time64_t ;
struct key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  key_check (struct key const*) ; 
 int key_is_dead (struct key const*,int /*<<< orphan*/ ) ; 
 struct key* keyring_ptr_to_key (void const*) ; 

__attribute__((used)) static int keyring_gc_check_iterator(const void *object, void *iterator_data)
{
	const struct key *key = keyring_ptr_to_key(object);
	time64_t *limit = iterator_data;

	key_check(key);
	return key_is_dead(key, *limit);
}