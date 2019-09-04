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
struct imx_media_fim {scalar_t__ num_skip; int /*<<< orphan*/  sd; int /*<<< orphan*/  icap_first_event; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX_MEDIA_EOF_TIMEOUT ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_warn (int /*<<< orphan*/ ,char*) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fim_acquire_first_ts(struct imx_media_fim *fim)
{
	unsigned long ret;

	if (!fim->enabled || fim->num_skip > 0)
		return;

	ret = wait_for_completion_timeout(
		&fim->icap_first_event,
		msecs_to_jiffies(IMX_MEDIA_EOF_TIMEOUT));
	if (ret == 0)
		v4l2_warn(fim->sd, "wait first icap event timeout\n");
}