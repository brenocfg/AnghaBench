#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct TYPE_2__ {scalar_t__ icsk_ca_state; } ;

/* Variables and functions */
 int const FLAG_CA_ALERT ; 
 int const FLAG_NOT_DUP ; 
 scalar_t__ TCP_CA_Open ; 
 TYPE_1__* inet_csk (struct sock const*) ; 

__attribute__((used)) static inline bool tcp_ack_is_dubious(const struct sock *sk, const int flag)
{
	return !(flag & FLAG_NOT_DUP) || (flag & FLAG_CA_ALERT) ||
		inet_csk(sk)->icsk_ca_state != TCP_CA_Open;
}