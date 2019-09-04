#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_6__ {TYPE_2__* rgd; } ;
struct gfs2_blkreserv {TYPE_3__ rs_rbm; } ;
struct TYPE_5__ {TYPE_1__* rd_gl; } ;
struct TYPE_4__ {int /*<<< orphan*/  gl_dstamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ktime_to_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool gfs2_rgrp_used_recently(const struct gfs2_blkreserv *rs,
				    u64 msecs)
{
	u64 tdiff;

	tdiff = ktime_to_ns(ktime_sub(ktime_get_real(),
                            rs->rs_rbm.rgd->rd_gl->gl_dstamp));

	return tdiff > (msecs * 1000 * 1000);
}