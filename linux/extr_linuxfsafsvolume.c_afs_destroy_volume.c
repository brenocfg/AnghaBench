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
struct afs_volume {int /*<<< orphan*/  cell; int /*<<< orphan*/  servers; } ;
struct afs_net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,struct afs_volume*) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  afs_put_cell (struct afs_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_put_serverlist (struct afs_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct afs_volume*) ; 

__attribute__((used)) static void afs_destroy_volume(struct afs_net *net, struct afs_volume *volume)
{
	_enter("%p", volume);

#ifdef CONFIG_AFS_FSCACHE
	ASSERTCMP(volume->cache, ==, NULL);
#endif

	afs_put_serverlist(net, volume->servers);
	afs_put_cell(net, volume->cell);
	kfree(volume);

	_leave(" [destroyed]");
}