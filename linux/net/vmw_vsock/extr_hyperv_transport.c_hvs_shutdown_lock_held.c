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
struct vmpipe_proto_header {int dummy; } ;
struct hvsock {int fin_sent; int /*<<< orphan*/  chan; } ;
struct hvs_send_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hvs_send_data (int /*<<< orphan*/ ,struct hvs_send_buf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hvs_shutdown_lock_held(struct hvsock *hvs, int mode)
{
	struct vmpipe_proto_header hdr;

	if (hvs->fin_sent || !hvs->chan)
		return;

	/* It can't fail: see hvs_channel_writable_bytes(). */
	(void)hvs_send_data(hvs->chan, (struct hvs_send_buf *)&hdr, 0);
	hvs->fin_sent = true;
}