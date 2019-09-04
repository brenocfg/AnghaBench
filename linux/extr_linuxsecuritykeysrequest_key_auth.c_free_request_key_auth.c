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
struct request_key_auth {struct request_key_auth* callout_info; scalar_t__ cred; int /*<<< orphan*/  dest_keyring; int /*<<< orphan*/  target_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  key_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct request_key_auth*) ; 
 int /*<<< orphan*/  put_cred (scalar_t__) ; 

__attribute__((used)) static void free_request_key_auth(struct request_key_auth *rka)
{
	if (!rka)
		return;
	key_put(rka->target_key);
	key_put(rka->dest_keyring);
	if (rka->cred)
		put_cred(rka->cred);
	kfree(rka->callout_info);
	kfree(rka);
}