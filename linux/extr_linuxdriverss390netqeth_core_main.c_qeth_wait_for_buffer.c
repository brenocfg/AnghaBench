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
struct qeth_cmd_buffer {int dummy; } ;
struct qeth_channel {int /*<<< orphan*/  wait_q; } ;

/* Variables and functions */
 struct qeth_cmd_buffer* qeth_get_buffer (struct qeth_channel*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct qeth_cmd_buffer *qeth_wait_for_buffer(struct qeth_channel *channel)
{
	struct qeth_cmd_buffer *buffer;
	wait_event(channel->wait_q,
		   ((buffer = qeth_get_buffer(channel)) != NULL));
	return buffer;
}