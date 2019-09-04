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
struct TYPE_2__ {scalar_t__ ext_bst; } ;
struct cs35l35_private {int /*<<< orphan*/  dev; int /*<<< orphan*/  pdn_done; TYPE_1__ pdata; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs35l35_wait_for_pdn(struct cs35l35_private *cs35l35)
{
	int ret;

	if (cs35l35->pdata.ext_bst) {
		usleep_range(5000, 5500);
		return 0;
	}

	reinit_completion(&cs35l35->pdn_done);

	ret = wait_for_completion_timeout(&cs35l35->pdn_done,
					  msecs_to_jiffies(100));
	if (ret == 0) {
		dev_err(cs35l35->dev, "PDN_DONE did not complete\n");
		return -ETIMEDOUT;
	}

	return 0;
}