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
struct subprocess_info {struct key* data; } ;
struct key {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int install_session_keyring_to_cred (struct cred*,struct key*) ; 

__attribute__((used)) static int umh_keys_init(struct subprocess_info *info, struct cred *cred)
{
	struct key *keyring = info->data;

	return install_session_keyring_to_cred(cred, keyring);
}