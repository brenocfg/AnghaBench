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
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip_ra_control (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_common_release (struct sock*) ; 

__attribute__((used)) static void raw_close(struct sock *sk, long timeout)
{
	/*
	 * Raw sockets may have direct kernel references. Kill them.
	 */
	ip_ra_control(sk, 0, NULL);

	sk_common_release(sk);
}