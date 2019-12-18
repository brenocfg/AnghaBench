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
struct afs_vlserver_list {int /*<<< orphan*/  lock; int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct afs_vlserver_list* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  servers ; 
 int /*<<< orphan*/  struct_size (struct afs_vlserver_list*,int /*<<< orphan*/ ,unsigned int) ; 

struct afs_vlserver_list *afs_alloc_vlserver_list(unsigned int nr_servers)
{
	struct afs_vlserver_list *vllist;

	vllist = kzalloc(struct_size(vllist, servers, nr_servers), GFP_KERNEL);
	if (vllist) {
		atomic_set(&vllist->usage, 1);
		rwlock_init(&vllist->lock);
	}

	return vllist;
}