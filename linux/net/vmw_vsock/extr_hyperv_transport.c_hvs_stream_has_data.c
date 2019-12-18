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
struct vsock_sock {int /*<<< orphan*/  peer_shutdown; struct hvsock* trans; } ;
struct hvsock {scalar_t__ recv_data_len; int /*<<< orphan*/  chan; } ;
typedef  int s64 ;

/* Variables and functions */
 int /*<<< orphan*/  SEND_SHUTDOWN ; 
 int hvs_channel_readable_payload (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s64 hvs_stream_has_data(struct vsock_sock *vsk)
{
	struct hvsock *hvs = vsk->trans;
	s64 ret;

	if (hvs->recv_data_len > 0)
		return 1;

	switch (hvs_channel_readable_payload(hvs->chan)) {
	case 1:
		ret = 1;
		break;
	case 0:
		vsk->peer_shutdown |= SEND_SHUTDOWN;
		ret = 0;
		break;
	default: /* -1 */
		ret = 0;
		break;
	}

	return ret;
}