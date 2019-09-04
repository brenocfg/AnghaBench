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
struct qcom_smd_channel {int /*<<< orphan*/ * bounce_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMD_CHANNEL_CLOSED ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_smd_channel_reset (struct qcom_smd_channel*) ; 
 int /*<<< orphan*/  qcom_smd_channel_set_callback (struct qcom_smd_channel*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_smd_channel_set_state (struct qcom_smd_channel*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qcom_smd_channel_close(struct qcom_smd_channel *channel)
{
	qcom_smd_channel_set_callback(channel, NULL);

	kfree(channel->bounce_buffer);
	channel->bounce_buffer = NULL;

	qcom_smd_channel_set_state(channel, SMD_CHANNEL_CLOSED);
	qcom_smd_channel_reset(channel);
}