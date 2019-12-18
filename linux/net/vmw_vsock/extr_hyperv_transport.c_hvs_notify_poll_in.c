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
struct hvsock {int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 int hvs_channel_readable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int hvs_notify_poll_in(struct vsock_sock *vsk, size_t target, bool *readable)
{
	struct hvsock *hvs = vsk->trans;

	*readable = hvs_channel_readable(hvs->chan);
	return 0;
}