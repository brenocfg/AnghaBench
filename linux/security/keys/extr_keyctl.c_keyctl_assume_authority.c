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
struct key {long serial; } ;
typedef  scalar_t__ key_serial_t ;

/* Variables and functions */
 long EINVAL ; 
 scalar_t__ IS_ERR (struct key*) ; 
 long PTR_ERR (struct key*) ; 
 struct key* key_get_instantiation_authkey (scalar_t__) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 long keyctl_change_reqkey_auth (struct key*) ; 

long keyctl_assume_authority(key_serial_t id)
{
	struct key *authkey;
	long ret;

	/* special key IDs aren't permitted */
	ret = -EINVAL;
	if (id < 0)
		goto error;

	/* we divest ourselves of authority if given an ID of 0 */
	if (id == 0) {
		ret = keyctl_change_reqkey_auth(NULL);
		goto error;
	}

	/* attempt to assume the authority temporarily granted to us whilst we
	 * instantiate the specified key
	 * - the authorisation key must be in the current task's keyrings
	 *   somewhere
	 */
	authkey = key_get_instantiation_authkey(id);
	if (IS_ERR(authkey)) {
		ret = PTR_ERR(authkey);
		goto error;
	}

	ret = keyctl_change_reqkey_auth(authkey);
	if (ret == 0)
		ret = authkey->serial;
	key_put(authkey);
error:
	return ret;
}