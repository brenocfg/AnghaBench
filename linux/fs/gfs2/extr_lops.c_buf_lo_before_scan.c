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
struct gfs2_log_header_host {int dummy; } ;
struct gfs2_jdesc {scalar_t__ jd_replayed_blocks; scalar_t__ jd_found_blocks; } ;

/* Variables and functions */

__attribute__((used)) static void buf_lo_before_scan(struct gfs2_jdesc *jd,
			       struct gfs2_log_header_host *head, int pass)
{
	if (pass != 0)
		return;

	jd->jd_found_blocks = 0;
	jd->jd_replayed_blocks = 0;
}