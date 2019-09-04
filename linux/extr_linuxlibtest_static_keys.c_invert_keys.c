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
struct test_key {struct static_key* key; } ;
struct static_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  invert_key (struct static_key*) ; 

__attribute__((used)) static void invert_keys(struct test_key *keys, int size)
{
	struct static_key *previous = NULL;
	int i;

	for (i = 0; i < size; i++) {
		if (previous != keys[i].key) {
			invert_key(keys[i].key);
			previous = keys[i].key;
		}
	}
}