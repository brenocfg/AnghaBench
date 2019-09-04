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
struct request_key_auth {struct key* target_key; } ;
struct key {int /*<<< orphan*/  serial; } ;

/* Variables and functions */
 struct request_key_auth* get_request_key_auth (struct key*) ; 
 int /*<<< orphan*/  kenter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  key_negate_and_link (struct key*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct key*) ; 
 int /*<<< orphan*/  key_negative_timeout ; 
 int /*<<< orphan*/  key_revoke (struct key*) ; 

void complete_request_key(struct key *authkey, int error)
{
	struct request_key_auth *rka = get_request_key_auth(authkey);
	struct key *key = rka->target_key;

	kenter("%d{%d},%d", authkey->serial, key->serial, error);

	if (error < 0)
		key_negate_and_link(key, key_negative_timeout, NULL, authkey);
	else
		key_revoke(authkey);
}