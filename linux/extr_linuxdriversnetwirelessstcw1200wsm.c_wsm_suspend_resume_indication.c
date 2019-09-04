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
typedef  int u32 ;
struct wsm_suspend_resume {int link_id; int stop; int multicast; int queue; } ;
struct wsm_buf {int dummy; } ;
struct cw1200_common {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int WSM_GET32 (struct wsm_buf*) ; 
 int /*<<< orphan*/  cw1200_suspend_resume (struct cw1200_common*,struct wsm_suspend_resume*) ; 

__attribute__((used)) static int wsm_suspend_resume_indication(struct cw1200_common *priv,
					 int link_id, struct wsm_buf *buf)
{
	u32 flags;
	struct wsm_suspend_resume arg;

	flags = WSM_GET32(buf);
	arg.link_id = link_id;
	arg.stop = !(flags & 1);
	arg.multicast = !!(flags & 8);
	arg.queue = (flags >> 1) & 3;

	cw1200_suspend_resume(priv, &arg);

	return 0;

underflow:
	return -EINVAL;
}