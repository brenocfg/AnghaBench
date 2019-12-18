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
 scalar_t__ dccp_ackvec_pending (struct sock const*) ; 
 scalar_t__ inet_csk_ack_scheduled (struct sock const*) ; 

__attribute__((used)) static inline int dccp_ack_pending(const struct sock *sk)
{
	return dccp_ackvec_pending(sk) || inet_csk_ack_scheduled(sk);
}