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
struct xt_hashlimit_htable {int /*<<< orphan*/  name; int /*<<< orphan*/  gc_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htable_remove_proc_entry (struct xt_hashlimit_htable*) ; 
 int /*<<< orphan*/  htable_selective_cleanup (struct xt_hashlimit_htable*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  select_all ; 
 int /*<<< orphan*/  vfree (struct xt_hashlimit_htable*) ; 

__attribute__((used)) static void htable_destroy(struct xt_hashlimit_htable *hinfo)
{
	cancel_delayed_work_sync(&hinfo->gc_work);
	htable_remove_proc_entry(hinfo);
	htable_selective_cleanup(hinfo, select_all);
	kfree(hinfo->name);
	vfree(hinfo);
}