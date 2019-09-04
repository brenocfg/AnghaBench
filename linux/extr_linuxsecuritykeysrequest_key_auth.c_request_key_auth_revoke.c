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
struct request_key_auth {int /*<<< orphan*/ * cred; } ;
struct key {int /*<<< orphan*/  serial; } ;

/* Variables and functions */
 struct request_key_auth* get_request_key_auth (struct key*) ; 
 int /*<<< orphan*/  kenter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_cred (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void request_key_auth_revoke(struct key *key)
{
	struct request_key_auth *rka = get_request_key_auth(key);

	kenter("{%d}", key->serial);

	if (rka->cred) {
		put_cred(rka->cred);
		rka->cred = NULL;
	}
}