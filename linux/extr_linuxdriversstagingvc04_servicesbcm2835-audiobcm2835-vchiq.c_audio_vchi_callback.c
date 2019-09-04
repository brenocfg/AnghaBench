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
struct TYPE_4__ {scalar_t__ cookie1; scalar_t__ cookie2; int /*<<< orphan*/  count; } ;
struct TYPE_3__ {int /*<<< orphan*/  success; } ;
struct vc_audio_msg {scalar_t__ type; TYPE_2__ complete; TYPE_1__ result; } ;
struct bcm2835_audio_instance {int /*<<< orphan*/  dev; int /*<<< orphan*/  alsa_stream; int /*<<< orphan*/  msg_avail_comp; int /*<<< orphan*/  result; int /*<<< orphan*/  vchi_handle; } ;
typedef  int /*<<< orphan*/  m ;
typedef  scalar_t__ VCHI_CALLBACK_REASON_T ;

/* Variables and functions */
 scalar_t__ const VCHI_CALLBACK_MSG_AVAILABLE ; 
 int /*<<< orphan*/  VCHI_FLAGS_NONE ; 
 scalar_t__ VC_AUDIO_MSG_TYPE_COMPLETE ; 
 scalar_t__ VC_AUDIO_MSG_TYPE_RESULT ; 
 scalar_t__ VC_AUDIO_WRITE_COOKIE1 ; 
 scalar_t__ VC_AUDIO_WRITE_COOKIE2 ; 
 int /*<<< orphan*/  bcm2835_playback_fifo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int vchi_msg_dequeue (int /*<<< orphan*/ ,struct vc_audio_msg*,int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void audio_vchi_callback(void *param,
				const VCHI_CALLBACK_REASON_T reason,
				void *msg_handle)
{
	struct bcm2835_audio_instance *instance = param;
	struct vc_audio_msg m;
	int msg_len;
	int status;

	if (reason != VCHI_CALLBACK_MSG_AVAILABLE)
		return;

	status = vchi_msg_dequeue(instance->vchi_handle,
				  &m, sizeof(m), &msg_len, VCHI_FLAGS_NONE);
	if (m.type == VC_AUDIO_MSG_TYPE_RESULT) {
		instance->result = m.result.success;
		complete(&instance->msg_avail_comp);
	} else if (m.type == VC_AUDIO_MSG_TYPE_COMPLETE) {
		if (m.complete.cookie1 != VC_AUDIO_WRITE_COOKIE1 ||
		    m.complete.cookie2 != VC_AUDIO_WRITE_COOKIE2)
			dev_err(instance->dev, "invalid cookie\n");
		else
			bcm2835_playback_fifo(instance->alsa_stream,
					      m.complete.count);
	} else {
		dev_err(instance->dev, "unexpected callback type=%d\n", m.type);
	}
}