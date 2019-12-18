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
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 int SCTP_AUTH_NUM_HMACS ; 
 int /*<<< orphan*/  crypto_free_shash (struct crypto_shash*) ; 
 int /*<<< orphan*/  kfree (struct crypto_shash**) ; 

void sctp_auth_destroy_hmacs(struct crypto_shash *auth_hmacs[])
{
	int i;

	if (!auth_hmacs)
		return;

	for (i = 0; i < SCTP_AUTH_NUM_HMACS; i++) {
		crypto_free_shash(auth_hmacs[i]);
	}
	kfree(auth_hmacs);
}