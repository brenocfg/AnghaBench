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
struct lavfi {int dummy; } ;
typedef  int /*<<< orphan*/  AVFilterPad ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  add_pad (struct lavfi*,int,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avfilter_pad_get_name (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void add_pads_direct(struct lavfi *c, int dir, AVFilterContext *f,
                            AVFilterPad *pads, int num_pads, bool first_init)
{
    for (int n = 0; n < num_pads; n++)
        add_pad(c, dir, n, f, n, avfilter_pad_get_name(pads, n), first_init);
}