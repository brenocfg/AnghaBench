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
struct sctp_shared_key {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_auth_shkey_destroy (struct sctp_shared_key*) ; 

void sctp_auth_shkey_release(struct sctp_shared_key *sh_key)
{
	if (refcount_dec_and_test(&sh_key->refcnt))
		sctp_auth_shkey_destroy(sh_key);
}