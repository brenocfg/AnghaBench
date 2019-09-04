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
typedef  int /*<<< orphan*/  u32 ;
struct tb_switch {int /*<<< orphan*/  uuid; } ;
struct nvm_auth_status {int /*<<< orphan*/  status; int /*<<< orphan*/  list; int /*<<< orphan*/  uuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ WARN_ON (int) ; 
 struct nvm_auth_status* __nvm_get_auth_status (struct tb_switch const*) ; 
 struct nvm_auth_status* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvm_auth_status_cache ; 
 int /*<<< orphan*/  nvm_auth_status_lock ; 

__attribute__((used)) static void nvm_set_auth_status(const struct tb_switch *sw, u32 status)
{
	struct nvm_auth_status *st;

	if (WARN_ON(!sw->uuid))
		return;

	mutex_lock(&nvm_auth_status_lock);
	st = __nvm_get_auth_status(sw);

	if (!st) {
		st = kzalloc(sizeof(*st), GFP_KERNEL);
		if (!st)
			goto unlock;

		memcpy(&st->uuid, sw->uuid, sizeof(st->uuid));
		INIT_LIST_HEAD(&st->list);
		list_add_tail(&st->list, &nvm_auth_status_cache);
	}

	st->status = status;
unlock:
	mutex_unlock(&nvm_auth_status_lock);
}