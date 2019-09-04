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
struct key_restriction {struct key const* key; } ;
struct key {struct key_restriction* restrict_link; int /*<<< orphan*/ * type; } ;

/* Variables and functions */
 int /*<<< orphan*/  key_type_keyring ; 

__attribute__((used)) static bool keyring_detect_restriction_cycle(const struct key *dest_keyring,
					     struct key_restriction *keyres)
{
	while (keyres && keyres->key &&
	       keyres->key->type == &key_type_keyring) {
		if (keyres->key == dest_keyring)
			return true;

		keyres = keyres->key->restrict_link;
	}

	return false;
}