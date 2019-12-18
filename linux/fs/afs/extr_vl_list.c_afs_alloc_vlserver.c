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
struct afs_vlserver {size_t name_len; unsigned short port; int /*<<< orphan*/  name; int /*<<< orphan*/  probe_lock; int /*<<< orphan*/  probe_wq; int /*<<< orphan*/  lock; int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct afs_vlserver* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  struct_size (struct afs_vlserver*,char const*,size_t) ; 

struct afs_vlserver *afs_alloc_vlserver(const char *name, size_t name_len,
					unsigned short port)
{
	struct afs_vlserver *vlserver;

	vlserver = kzalloc(struct_size(vlserver, name, name_len + 1),
			   GFP_KERNEL);
	if (vlserver) {
		atomic_set(&vlserver->usage, 1);
		rwlock_init(&vlserver->lock);
		init_waitqueue_head(&vlserver->probe_wq);
		spin_lock_init(&vlserver->probe_lock);
		vlserver->name_len = name_len;
		vlserver->port = port;
		memcpy(vlserver->name, name, name_len);
	}
	return vlserver;
}