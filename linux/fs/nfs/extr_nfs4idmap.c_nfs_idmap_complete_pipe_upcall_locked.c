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
struct key {int dummy; } ;
struct idmap {TYPE_1__* idmap_upcall_data; } ;
struct TYPE_2__ {struct key* authkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete_request_key (struct key*,int) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static void
nfs_idmap_complete_pipe_upcall_locked(struct idmap *idmap, int ret)
{
	struct key *authkey = idmap->idmap_upcall_data->authkey;

	kfree(idmap->idmap_upcall_data);
	idmap->idmap_upcall_data = NULL;
	complete_request_key(authkey, ret);
	key_put(authkey);
}