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
struct vc_audio_msg {int /*<<< orphan*/  type; } ;
struct bcm2835_audio_instance {int result; int /*<<< orphan*/  dev; int /*<<< orphan*/  msg_avail_comp; int /*<<< orphan*/  vchi_handle; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int vchi_queue_kernel_message (int /*<<< orphan*/ ,struct vc_audio_msg*,int) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm2835_audio_send_msg_locked(struct bcm2835_audio_instance *instance,
					 struct vc_audio_msg *m, bool wait)
{
	int status;

	if (wait) {
		instance->result = -1;
		init_completion(&instance->msg_avail_comp);
	}

	status = vchi_queue_kernel_message(instance->vchi_handle,
					   m, sizeof(*m));
	if (status) {
		dev_err(instance->dev,
			"vchi message queue failed: %d, msg=%d\n",
			status, m->type);
		return -EIO;
	}

	if (wait) {
		if (!wait_for_completion_timeout(&instance->msg_avail_comp,
						 msecs_to_jiffies(10 * 1000))) {
			dev_err(instance->dev,
				"vchi message timeout, msg=%d\n", m->type);
			return -ETIMEDOUT;
		} else if (instance->result) {
			dev_err(instance->dev,
				"vchi message response error:%d, msg=%d\n",
				instance->result, m->type);
			return -EIO;
		}
	}

	return 0;
}