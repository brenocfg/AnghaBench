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
struct qcom_smd_edge {int /*<<< orphan*/  dev; } ;
struct qcom_smd_channel {int state; int /*<<< orphan*/  name; struct qcom_smd_edge* edge; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_TX_CHANNEL_FLAG (struct qcom_smd_channel*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET_TX_CHANNEL_INFO (struct qcom_smd_channel*,int,int) ; 
 int SMD_CHANNEL_OPENED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fCD ; 
 int /*<<< orphan*/  fCTS ; 
 int /*<<< orphan*/  fDSR ; 
 int /*<<< orphan*/  fSTATE ; 
 int /*<<< orphan*/  qcom_smd_signal_channel (struct qcom_smd_channel*) ; 

__attribute__((used)) static void qcom_smd_channel_set_state(struct qcom_smd_channel *channel,
				       int state)
{
	struct qcom_smd_edge *edge = channel->edge;
	bool is_open = state == SMD_CHANNEL_OPENED;

	if (channel->state == state)
		return;

	dev_dbg(&edge->dev, "set_state(%s, %d)\n", channel->name, state);

	SET_TX_CHANNEL_FLAG(channel, fDSR, is_open);
	SET_TX_CHANNEL_FLAG(channel, fCTS, is_open);
	SET_TX_CHANNEL_FLAG(channel, fCD, is_open);

	SET_TX_CHANNEL_INFO(channel, state, state);
	SET_TX_CHANNEL_FLAG(channel, fSTATE, 1);

	channel->state = state;
	qcom_smd_signal_channel(channel);
}