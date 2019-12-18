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
struct modsig {int dummy; } ;
struct key {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct key*) ; 
 int PTR_ERR (struct key*) ; 
 int ima_modsig_verify (struct key*,struct modsig const*) ; 
 struct key* integrity_keyring_from_id (unsigned int const) ; 

int integrity_modsig_verify(const unsigned int id, const struct modsig *modsig)
{
	struct key *keyring;

	keyring = integrity_keyring_from_id(id);
	if (IS_ERR(keyring))
		return PTR_ERR(keyring);

	return ima_modsig_verify(keyring, modsig);
}