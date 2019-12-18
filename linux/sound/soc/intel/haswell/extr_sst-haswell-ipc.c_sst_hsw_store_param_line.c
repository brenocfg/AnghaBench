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
typedef  int /*<<< orphan*/  u8 ;
struct sst_hsw {int param_idx_w; int /*<<< orphan*/ * param_buf; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  WAVES_PARAM_COUNT ; 
 int WAVES_PARAM_LINES ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int sst_hsw_store_param_line(struct sst_hsw *hsw, u8 *buf)
{
	/* save line to the first available position of param buffer */
	if (hsw->param_idx_w > WAVES_PARAM_LINES - 1) {
		dev_warn(hsw->dev, "warning: param buffer overflow!\n");
		return -EPERM;
	}
	memcpy(hsw->param_buf[hsw->param_idx_w], buf, WAVES_PARAM_COUNT);
	hsw->param_idx_w++;
	return 0;
}