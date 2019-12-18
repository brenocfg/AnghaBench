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
struct hvsock {int /*<<< orphan*/ * chan; } ;

/* Variables and functions */

__attribute__((used)) static bool hvs_stream_is_active(struct vsock_sock *vsk)
{
	struct hvsock *hvs = vsk->trans;

	return hvs->chan != NULL;
}