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
 int /*<<< orphan*/  EMSG2 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bf_crypt_save () ; 
 int crypt_busy ; 
 int /*<<< orphan*/  e_intern2 ; 
 int /*<<< orphan*/ * keys ; 
 scalar_t__ saved_crypt_method ; 
 int /*<<< orphan*/ * saved_keys ; 
 scalar_t__ use_crypt_method ; 

void
crypt_push_state()
{
    if (crypt_busy == 1)
    {
	/* save the state */
	if (use_crypt_method == 0)
	{
	    saved_keys[0] = keys[0];
	    saved_keys[1] = keys[1];
	    saved_keys[2] = keys[2];
	}
	else
	    bf_crypt_save();
	saved_crypt_method = use_crypt_method;
    }
    else if (crypt_busy > 1)
	EMSG2(_(e_intern2), "crypt_push_state()");
    ++crypt_busy;
}