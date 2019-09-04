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
struct TYPE_2__ {scalar_t__ classid; } ;
struct tcindex_filter_result {TYPE_1__ res; int /*<<< orphan*/  exts; } ;

/* Variables and functions */
 scalar_t__ tcf_exts_has_actions (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int tcindex_filter_is_set(struct tcindex_filter_result *r)
{
	return tcf_exts_has_actions(&r->exts) || r->res.classid;
}