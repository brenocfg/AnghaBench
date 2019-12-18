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
struct key_type {int dummy; } ;
struct key_restriction {struct key_type* keytype; int /*<<< orphan*/ * key; int /*<<< orphan*/  check; } ;
struct key {int /*<<< orphan*/  sem; struct key_restriction* restrict_link; scalar_t__ description; int /*<<< orphan*/  serial; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kenter (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  key_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kleave (char*) ; 
 int /*<<< orphan*/  restrict_link_reject ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void keyring_restriction_gc(struct key *keyring, struct key_type *dead_type)
{
	struct key_restriction *keyres;

	kenter("%x{%s}", keyring->serial, keyring->description ?: "");

	/*
	 * keyring->restrict_link is only assigned at key allocation time
	 * or with the key type locked, so the only values that could be
	 * concurrently assigned to keyring->restrict_link are for key
	 * types other than dead_type. Given this, it's ok to check
	 * the key type before acquiring keyring->sem.
	 */
	if (!dead_type || !keyring->restrict_link ||
	    keyring->restrict_link->keytype != dead_type) {
		kleave(" [no restriction gc]");
		return;
	}

	/* Lock the keyring to ensure that a link is not in progress */
	down_write(&keyring->sem);

	keyres = keyring->restrict_link;

	keyres->check = restrict_link_reject;

	key_put(keyres->key);
	keyres->key = NULL;
	keyres->keytype = NULL;

	up_write(&keyring->sem);

	kleave(" [restriction gc]");
}