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
struct snd_seq_port_subs_info {int /*<<< orphan*/ * close; int /*<<< orphan*/ * open; int /*<<< orphan*/  list_mutex; int /*<<< orphan*/  list_lock; scalar_t__ exclusive; scalar_t__ count; int /*<<< orphan*/  list_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void port_subs_info_init(struct snd_seq_port_subs_info *grp)
{
	INIT_LIST_HEAD(&grp->list_head);
	grp->count = 0;
	grp->exclusive = 0;
	rwlock_init(&grp->list_lock);
	init_rwsem(&grp->list_mutex);
	grp->open = NULL;
	grp->close = NULL;
}