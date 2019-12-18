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
 int /*<<< orphan*/  key_get (struct key*) ; 
 scalar_t__ key_is_dead (struct key*,int /*<<< orphan*/ ) ; 
 struct key* keyring_ptr_to_key (void*) ; 

__attribute__((used)) static bool keyring_gc_select_iterator(void *object, void *iterator_data)
{
	struct key *key = keyring_ptr_to_key(object);
	time64_t *limit = iterator_data;

	if (key_is_dead(key, *limit))
		return false;
	key_get(key);
	return true;
}