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
struct TYPE_2__ {scalar_t__ len; } ;
struct mp_pass_perf {int dummy; } ;
struct pass_info {TYPE_1__ desc; struct mp_pass_perf perf; } ;
struct gl_video {size_t pass_idx; struct pass_info* pass; } ;

/* Variables and functions */
 size_t VO_PASS_PERF_MAX ; 
 int /*<<< orphan*/  bstr0 (char*) ; 
 int /*<<< orphan*/  bstr_xappend (struct gl_video*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pass_record(struct gl_video *p, struct mp_pass_perf perf)
{
    if (!p->pass || p->pass_idx == VO_PASS_PERF_MAX)
        return;

    struct pass_info *pass = &p->pass[p->pass_idx];
    pass->perf = perf;

    if (pass->desc.len == 0)
        bstr_xappend(p, &pass->desc, bstr0("(unknown)"));

    p->pass_idx++;
}