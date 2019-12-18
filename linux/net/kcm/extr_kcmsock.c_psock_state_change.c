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
 int /*<<< orphan*/  EPIPE ; 
 int /*<<< orphan*/  report_csk_error (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void psock_state_change(struct sock *sk)
{
	/* TCP only does a EPOLLIN for a half close. Do a EPOLLHUP here
	 * since application will normally not poll with EPOLLIN
	 * on the TCP sockets.
	 */

	report_csk_error(sk, EPIPE);
}