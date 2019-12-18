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
struct cls_fl_filter {int /*<<< orphan*/  rwork; int /*<<< orphan*/  exts; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  __fl_destroy_filter (struct cls_fl_filter*) ; 
 int /*<<< orphan*/  fl_destroy_filter_work ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ tcf_exts_get_net (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __fl_put(struct cls_fl_filter *f)
{
	if (!refcount_dec_and_test(&f->refcnt))
		return;

	if (tcf_exts_get_net(&f->exts))
		tcf_queue_work(&f->rwork, fl_destroy_filter_work);
	else
		__fl_destroy_filter(f);
}