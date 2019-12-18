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
struct sst_hsw {scalar_t__ param_buf; scalar_t__ param_idx_r; scalar_t__ param_idx_w; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

void sst_hsw_reset_param_buf(struct sst_hsw *hsw)
{
	hsw->param_idx_w = 0;
	hsw->param_idx_r = 0;
	memset((void *)hsw->param_buf, 0, sizeof(hsw->param_buf));
}