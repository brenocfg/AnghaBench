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
struct TYPE_2__ {int /*<<< orphan*/  exts; } ;
struct tcindex_filter {TYPE_1__ result; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tcindex_filter*) ; 
 int /*<<< orphan*/  tcf_exts_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_exts_put_net (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __tcindex_destroy_fexts(struct tcindex_filter *f)
{
	tcf_exts_destroy(&f->result.exts);
	tcf_exts_put_net(&f->result.exts);
	kfree(f);
}