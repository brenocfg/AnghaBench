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
 scalar_t__ memcmp (void*,void*,unsigned int) ; 

__attribute__((used)) static inline bool keys_match(void *key, void *test_key, unsigned key_size)
{
	bool match = true;

	if (memcmp(key, test_key, key_size))
		match = false;

	return match;
}