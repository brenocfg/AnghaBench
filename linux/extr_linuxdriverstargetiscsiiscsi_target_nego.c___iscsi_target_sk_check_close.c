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
struct sock {scalar_t__ sk_state; } ;

/* Variables and functions */
 scalar_t__ TCP_CLOSE ; 
 scalar_t__ TCP_CLOSE_WAIT ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static bool __iscsi_target_sk_check_close(struct sock *sk)
{
	if (sk->sk_state == TCP_CLOSE_WAIT || sk->sk_state == TCP_CLOSE) {
		pr_debug("__iscsi_target_sk_check_close: TCP_CLOSE_WAIT|TCP_CLOSE,"
			"returning FALSE\n");
		return true;
	}
	return false;
}