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
struct mp_pass_perf {scalar_t__ peak; scalar_t__ avg; scalar_t__ last; } ;
struct mp_frame_perf {int count; int /*<<< orphan*/ * desc; struct mp_pass_perf* perf; } ;

/* Variables and functions */
 char* talloc_asprintf_append (char*,char*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static char *asprint_perf(char *res, struct mp_frame_perf *perf)
{
    for (int i = 0; i < perf->count; i++) {
        struct mp_pass_perf *pass = &perf->perf[i];
        res = talloc_asprintf_append(res,
                  "- %s: last %dus avg %dus peak %dus\n", perf->desc[i],
                  (int)pass->last/1000, (int)pass->avg/1000, (int)pass->peak/1000);
    }

    return res;
}