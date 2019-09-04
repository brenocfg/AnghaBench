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
struct wsm_join_complete {int /*<<< orphan*/  status; } ;
struct wsm_buf {int dummy; } ;
struct cw1200_common {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WSM_GET32 (struct wsm_buf*) ; 
 int /*<<< orphan*/  cw1200_join_complete_cb (struct cw1200_common*,struct wsm_join_complete*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wsm_join_complete_indication(struct cw1200_common *priv,
					struct wsm_buf *buf)
{
	struct wsm_join_complete arg;
	arg.status = WSM_GET32(buf);
	pr_debug("[WSM] Join complete indication, status: %d\n", arg.status);
	cw1200_join_complete_cb(priv, &arg);

	return 0;

underflow:
	return -EINVAL;
}