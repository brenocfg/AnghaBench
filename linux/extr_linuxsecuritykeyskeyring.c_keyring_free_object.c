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
 int /*<<< orphan*/  key_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keyring_ptr_to_key (void*) ; 

__attribute__((used)) static void keyring_free_object(void *object)
{
	key_put(keyring_ptr_to_key(object));
}