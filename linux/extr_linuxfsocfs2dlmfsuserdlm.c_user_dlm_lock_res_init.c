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
struct user_lock_res {scalar_t__ l_namelen; int /*<<< orphan*/  l_name; void* l_blocking; void* l_requested; void* l_level; int /*<<< orphan*/  l_event; int /*<<< orphan*/  l_lock; } ;
struct TYPE_2__ {scalar_t__ len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 void* DLM_LOCK_IV ; 
 scalar_t__ USER_DLM_LOCK_ID_MAX_LEN ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct user_lock_res*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void user_dlm_lock_res_init(struct user_lock_res *lockres,
			    struct dentry *dentry)
{
	memset(lockres, 0, sizeof(*lockres));

	spin_lock_init(&lockres->l_lock);
	init_waitqueue_head(&lockres->l_event);
	lockres->l_level = DLM_LOCK_IV;
	lockres->l_requested = DLM_LOCK_IV;
	lockres->l_blocking = DLM_LOCK_IV;

	/* should have been checked before getting here. */
	BUG_ON(dentry->d_name.len >= USER_DLM_LOCK_ID_MAX_LEN);

	memcpy(lockres->l_name,
	       dentry->d_name.name,
	       dentry->d_name.len);
	lockres->l_namelen = dentry->d_name.len;
}