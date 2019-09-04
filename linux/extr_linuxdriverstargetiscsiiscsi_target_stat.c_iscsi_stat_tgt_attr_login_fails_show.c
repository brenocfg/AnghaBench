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
typedef  int u32 ;
struct iscsi_login_stats {int redirects; int authorize_fails; int authenticate_fails; int negotiate_fails; int other_fails; int /*<<< orphan*/  lock; } ;
struct iscsi_tiqn {struct iscsi_login_stats login_stats; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct iscsi_tiqn* iscsi_tgt_attr_tiqn (struct config_item*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t iscsi_stat_tgt_attr_login_fails_show(struct config_item *item,
		char *page)
{
	struct iscsi_tiqn *tiqn = iscsi_tgt_attr_tiqn(item);
	struct iscsi_login_stats *lstat = &tiqn->login_stats;
	u32 fail_count;

	spin_lock(&lstat->lock);
	fail_count = (lstat->redirects + lstat->authorize_fails +
			lstat->authenticate_fails + lstat->negotiate_fails +
			lstat->other_fails);
	spin_unlock(&lstat->lock);

	return snprintf(page, PAGE_SIZE, "%u\n", fail_count);
}