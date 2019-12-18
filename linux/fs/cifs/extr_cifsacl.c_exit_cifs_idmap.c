#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  thread_keyring; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ cifs_idmap_key_type ; 
 int /*<<< orphan*/  key_revoke (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_cred (TYPE_2__*) ; 
 TYPE_2__* root_cred ; 
 int /*<<< orphan*/  unregister_key_type (TYPE_1__*) ; 

void
exit_cifs_idmap(void)
{
	key_revoke(root_cred->thread_keyring);
	unregister_key_type(&cifs_idmap_key_type);
	put_cred(root_cred);
	cifs_dbg(FYI, "Unregistered %s key type\n", cifs_idmap_key_type.name);
}