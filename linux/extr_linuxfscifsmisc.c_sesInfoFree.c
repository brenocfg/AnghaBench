#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct cifs_ses* response; } ;
struct cifs_ses {int /*<<< orphan*/  iface_list; TYPE_1__ auth_key; int /*<<< orphan*/  domainName; int /*<<< orphan*/  user_name; struct cifs_ses* password; int /*<<< orphan*/  serverNOS; int /*<<< orphan*/  serverDomain; int /*<<< orphan*/  serverOS; } ;

/* Variables and functions */
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (struct cifs_ses*) ; 
 int /*<<< orphan*/  sesInfoAllocCount ; 

void
sesInfoFree(struct cifs_ses *buf_to_free)
{
	if (buf_to_free == NULL) {
		cifs_dbg(FYI, "Null buffer passed to sesInfoFree\n");
		return;
	}

	atomic_dec(&sesInfoAllocCount);
	kfree(buf_to_free->serverOS);
	kfree(buf_to_free->serverDomain);
	kfree(buf_to_free->serverNOS);
	kzfree(buf_to_free->password);
	kfree(buf_to_free->user_name);
	kfree(buf_to_free->domainName);
	kzfree(buf_to_free->auth_key.response);
	kfree(buf_to_free->iface_list);
	kzfree(buf_to_free);
}