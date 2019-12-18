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
struct proto {scalar_t__ recvmsg; scalar_t__ sendmsg; scalar_t__ sendpage; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 scalar_t__ tcp_recvmsg ; 
 scalar_t__ tcp_sendmsg ; 
 scalar_t__ tcp_sendpage ; 

__attribute__((used)) static int tcp_bpf_assert_proto_ops(struct proto *ops)
{
	/* In order to avoid retpoline, we make assumptions when we call
	 * into ops if e.g. a psock is not present. Make sure they are
	 * indeed valid assumptions.
	 */
	return ops->recvmsg  == tcp_recvmsg &&
	       ops->sendmsg  == tcp_sendmsg &&
	       ops->sendpage == tcp_sendpage ? 0 : -ENOTSUPP;
}