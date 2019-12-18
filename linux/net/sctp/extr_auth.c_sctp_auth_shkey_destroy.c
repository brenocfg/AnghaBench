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
struct sctp_shared_key {int /*<<< orphan*/ * key; int /*<<< orphan*/  key_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  kfree (struct sctp_shared_key*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_auth_key_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sctp_auth_shkey_destroy(struct sctp_shared_key *sh_key)
{
	BUG_ON(!list_empty(&sh_key->key_list));
	sctp_auth_key_put(sh_key->key);
	sh_key->key = NULL;
	kfree(sh_key);
}