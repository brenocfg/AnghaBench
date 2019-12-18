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
struct key {int /*<<< orphan*/  keys; } ;

/* Variables and functions */
 int /*<<< orphan*/  assoc_array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  keyring_publish_name (struct key*) ; 

__attribute__((used)) static int keyring_instantiate(struct key *keyring,
			       struct key_preparsed_payload *prep)
{
	assoc_array_init(&keyring->keys);
	/* make the keyring available by name if it has one */
	keyring_publish_name(keyring);
	return 0;
}