#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  fu_rcuhead; } ;
struct file {int f_flags; int /*<<< orphan*/  f_mode; int /*<<< orphan*/  f_pos_lock; int /*<<< orphan*/  f_lock; TYPE_2__ f_owner; int /*<<< orphan*/  f_count; TYPE_1__ f_u; int /*<<< orphan*/  f_cred; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct file* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OPEN_FMODE (int) ; 
 int /*<<< orphan*/  atomic_long_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  eventpoll_init_file (struct file*) ; 
 int /*<<< orphan*/  file_free_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filp_cachep ; 
 int /*<<< orphan*/  get_cred (struct cred const*) ; 
 struct file* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int security_file_alloc (struct file*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct file *__alloc_file(int flags, const struct cred *cred)
{
	struct file *f;
	int error;

	f = kmem_cache_zalloc(filp_cachep, GFP_KERNEL);
	if (unlikely(!f))
		return ERR_PTR(-ENOMEM);

	f->f_cred = get_cred(cred);
	error = security_file_alloc(f);
	if (unlikely(error)) {
		file_free_rcu(&f->f_u.fu_rcuhead);
		return ERR_PTR(error);
	}

	atomic_long_set(&f->f_count, 1);
	rwlock_init(&f->f_owner.lock);
	spin_lock_init(&f->f_lock);
	mutex_init(&f->f_pos_lock);
	eventpoll_init_file(f);
	f->f_flags = flags;
	f->f_mode = OPEN_FMODE(flags);
	/* f->f_version: 0 */

	return f;
}