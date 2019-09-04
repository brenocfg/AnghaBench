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
struct cls_fl_filter {int /*<<< orphan*/  exts; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct cls_fl_filter*) ; 
 int /*<<< orphan*/  tcf_exts_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_exts_put_net (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __fl_destroy_filter(struct cls_fl_filter *f)
{
	tcf_exts_destroy(&f->exts);
	tcf_exts_put_net(&f->exts);
	kfree(f);
}