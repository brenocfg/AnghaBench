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
 int /*<<< orphan*/  bf_crypt_restore () ; 
 int crypt_busy ; 
 int /*<<< orphan*/ * keys ; 
 scalar_t__ saved_crypt_method ; 
 int /*<<< orphan*/ * saved_keys ; 
 scalar_t__ use_crypt_method ; 

void
crypt_pop_state()
{
    --crypt_busy;
    if (crypt_busy == 1)
    {
	use_crypt_method = saved_crypt_method;
	if (use_crypt_method == 0)
	{
	    keys[0] = saved_keys[0];
	    keys[1] = saved_keys[1];
	    keys[2] = saved_keys[2];
	}
	else
	    bf_crypt_restore();
    }
}