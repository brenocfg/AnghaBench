#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* ls_ops; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_wdack; TYPE_2__ sd_lockstruct; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  lm_proto_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t wdack_store(struct gfs2_sbd *sdp, const char *buf, size_t len)
{
	int ret, val;

	ret = kstrtoint(buf, 0, &val);
	if (ret)
		return ret;

	if ((val == 1) &&
	    !strcmp(sdp->sd_lockstruct.ls_ops->lm_proto_name, "lock_dlm"))
		complete(&sdp->sd_wdack);
	else
		return -EINVAL;
	return len;
}