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
struct reg_regdb_apply_request {int /*<<< orphan*/  list; struct ieee80211_regdomain const* regdom; } ;
struct ieee80211_regdomain {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct ieee80211_regdomain const*) ; 
 struct reg_regdb_apply_request* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reg_regdb_apply_list ; 
 int /*<<< orphan*/  reg_regdb_apply_mutex ; 
 int /*<<< orphan*/  reg_regdb_work ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int reg_schedule_apply(const struct ieee80211_regdomain *regdom)
{
	struct reg_regdb_apply_request *request;

	request = kzalloc(sizeof(struct reg_regdb_apply_request), GFP_KERNEL);
	if (!request) {
		kfree(regdom);
		return -ENOMEM;
	}

	request->regdom = regdom;

	mutex_lock(&reg_regdb_apply_mutex);
	list_add_tail(&request->list, &reg_regdb_apply_list);
	mutex_unlock(&reg_regdb_apply_mutex);

	schedule_work(&reg_regdb_work);
	return 0;
}