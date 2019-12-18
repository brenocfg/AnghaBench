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
struct mpgl_osd {int /*<<< orphan*/  osd_res; int /*<<< orphan*/  osd; } ;
struct mp_osd_res {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  osd_resize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_res (struct mpgl_osd*,struct mp_osd_res,int) ; 

void mpgl_osd_resize(struct mpgl_osd *ctx, struct mp_osd_res res, int stereo_mode)
{
    set_res(ctx, res, stereo_mode);
    osd_resize(ctx->osd, ctx->osd_res);
}