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
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  hvs_channel_writable_bytes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s64 hvs_stream_has_space(struct vsock_sock *vsk)
{
	struct hvsock *hvs = vsk->trans;

	return hvs_channel_writable_bytes(hvs->chan);
}