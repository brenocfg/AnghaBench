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
struct vsock_sock {struct hvsock* trans; } ;
struct vmbus_channel {int dummy; } ;
struct hvsock {struct vmbus_channel* chan; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 scalar_t__ hvs_channel_writable_bytes (struct vmbus_channel*) ; 
 int /*<<< orphan*/  hvs_clear_channel_pending_send_size (struct vmbus_channel*) ; 
 int /*<<< orphan*/  hvs_set_channel_pending_send_size (struct vmbus_channel*) ; 

__attribute__((used)) static s64 hvs_stream_has_space(struct vsock_sock *vsk)
{
	struct hvsock *hvs = vsk->trans;
	struct vmbus_channel *chan = hvs->chan;
	s64 ret;

	ret = hvs_channel_writable_bytes(chan);
	if (ret > 0)  {
		hvs_clear_channel_pending_send_size(chan);
	} else {
		/* See hvs_channel_cb() */
		hvs_set_channel_pending_send_size(chan);

		/* Re-check the writable bytes to avoid race */
		ret = hvs_channel_writable_bytes(chan);
		if (ret > 0)
			hvs_clear_channel_pending_send_size(chan);
	}

	return ret;
}