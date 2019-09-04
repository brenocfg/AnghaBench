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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  AVRational ;

/* Variables and functions */
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 double MP_NOPTS_VALUE ; 
 double av_q2d (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_def_tb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  llrint (double) ; 

int64_t mp_pts_to_av(double mp_pts, AVRational *tb)
{
    AVRational b = get_def_tb(tb);
    return mp_pts == MP_NOPTS_VALUE ? AV_NOPTS_VALUE : llrint(mp_pts / av_q2d(b));
}